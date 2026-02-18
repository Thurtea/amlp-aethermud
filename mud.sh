#!/bin/bash

# AMLP-MUD Unified Control Script
# Usage: ./mud.sh <command> [options]

MUDLIB_DIR="$(cd "$(dirname "$0")" && pwd)"
SERVER_BIN="$MUDLIB_DIR/build/driver"
PID_FILE="$MUDLIB_DIR/mud.pid"
LOG_FILE="$MUDLIB_DIR/lib/log/server.log"
DEFAULT_PORT=3000

cd "$MUDLIB_DIR" || exit 1

# --- SECTION 1: BUILD COMMANDS ---

build_driver() {
    echo "[*] Building driver..."
    make driver
}

rebuild_driver() {
    echo "[*] Cleaning and rebuilding driver..."
    make clean && make driver
}

clean_build() {
    echo "[*] Cleaning build artifacts..."
    make clean
}

# --- SECTION 2: RUNTIME COMMANDS ---

port_listener_pid() {
    local pid=""
    if command -v lsof >/dev/null 2>&1; then
        pid=$(lsof -tiTCP:"$DEFAULT_PORT" -sTCP:LISTEN 2>/dev/null || true)
    elif command -v ss >/dev/null 2>&1; then
        # Fix #4: extract PID from iproute2 ss -ltnp format:
        #   users:(("driver",pid=1234,fd=3))
        # match() locates "pid=NNN", then substr() extracts the digits.
        pid=$(ss -ltnp 2>/dev/null | awk -v port=":$DEFAULT_PORT" '
            $4 ~ port {
                match($0, /pid=[0-9]+/)
                if (RSTART) { print substr($0, RSTART+4, RLENGTH-4); exit }
            }')
    else
        pid=""
    fi
    echo "$pid"
}

# Read and validate the PID file.  Prints the numeric PID to stdout on
# success.  On failure (missing, empty, or non-numeric content) prints a
# message to stderr, removes the file, and returns 1.
# Fix #6: validates PID file contents before use.
read_pid_file() {
    local pid
    pid=$(cat "$PID_FILE" 2>/dev/null | head -1 | tr -d '[:space:]')
    if ! [[ "$pid" =~ ^[0-9]+$ ]]; then
        echo "[*] Corrupt or empty PID file, removing..." >&2
        rm -f "$PID_FILE"
        return 1
    fi
    echo "$pid"
}

start_server() {
    # Fix #7: all variables are local to this function.
    local PID EXIST_PID SERVER_PID ACTIVE_PID WS_PORT i

    if [ -f "$PID_FILE" ]; then
        if PID=$(read_pid_file); then
            if kill -0 "$PID" 2>/dev/null; then
                echo "[*] Server already running (PID: $PID)"
                return 1
            else
                echo "[*] Removing stale PID file..."
                rm -f "$PID_FILE"
            fi
        fi
        # read_pid_file already removed a corrupt file and printed a message.
    fi

    if [ ! -x "$SERVER_BIN" ]; then
        echo "[✗] Error: Server binary not found or not executable"
        echo "    Run: ./mud.sh build"
        return 1
    fi

    EXIST_PID=$(port_listener_pid | head -1)
    if [ -n "$EXIST_PID" ]; then
        echo "[✗] Error: Port $DEFAULT_PORT in use by PID $EXIST_PID."
        echo "    Run: ./mud.sh stop"
        return 1
    fi

    mkdir -p "$(dirname "$LOG_FILE")"
    echo "[*] Starting AMLP-MUD server on port $DEFAULT_PORT..."
    WS_PORT=$((DEFAULT_PORT + 1))
    nohup "$SERVER_BIN" "$DEFAULT_PORT" "$WS_PORT" "lib/secure/master.lpc" >> "$LOG_FILE" 2>&1 &
    SERVER_PID=$!

    # Fix #9: retry loop instead of fixed sleep — poll up to 5 × 0.5 s.
    ACTIVE_PID=""
    for i in {1..5}; do
        sleep 0.5
        # Fix #2: pipe through head -1 so ACTIVE_PID is always a single PID.
        ACTIVE_PID=$(port_listener_pid | head -1)
        [ -n "$ACTIVE_PID" ] && break
    done

    if [ -n "$ACTIVE_PID" ]; then
        echo "$ACTIVE_PID" > "$PID_FILE"
        echo "[✓] Server started (PID: $ACTIVE_PID)"
        echo "    Log file: $LOG_FILE"
        return 0
    fi

    if kill -0 "$SERVER_PID" 2>/dev/null; then
        echo "$SERVER_PID" > "$PID_FILE"
        echo "[✓] Server started (PID: $SERVER_PID) — port listener not detected yet"
        echo "    Log file: $LOG_FILE"
        return 0
    fi

    echo "[✗] Server failed to start. Check $LOG_FILE"
    rm -f "$PID_FILE"
    return 1
}

stop_server() {
    # Fix #7: all variables are local to this function.
    local PID ORPHAN FALLBACK i

    if [ ! -f "$PID_FILE" ]; then
        echo "[*] Server not running (no PID file)"
        ORPHAN=$(port_listener_pid | head -n1)
        if [ -n "$ORPHAN" ]; then
            echo "[*] Found orphaned server process on port (PID: $ORPHAN)"
            echo "[*] Killing orphaned process..."
            kill -TERM "$ORPHAN" 2>/dev/null
            sleep 1
            if kill -0 "$ORPHAN" 2>/dev/null; then
                kill -KILL "$ORPHAN" 2>/dev/null
            fi
            echo "[✓] Orphaned process terminated"
        fi
        return 0
    fi

    # Fix #6: validate PID file before use.
    if ! PID=$(read_pid_file); then
        # File was corrupt; read_pid_file already removed it.
        FALLBACK=$(port_listener_pid | head -n1)
        if [ -n "$FALLBACK" ]; then
            echo "[*] Found listener PID $FALLBACK — killing it."
            kill -TERM "$FALLBACK" 2>/dev/null || true
            sleep 1
            if kill -0 "$FALLBACK" 2>/dev/null; then
                kill -KILL "$FALLBACK" 2>/dev/null || true
            fi
            echo "[✓] Listener process terminated"
        fi
        return 0
    fi

    if ! kill -0 "$PID" 2>/dev/null; then
        echo "[*] Server not running (stale PID: $PID)"
        rm -f "$PID_FILE"
        FALLBACK=$(port_listener_pid | head -n1)
        if [ -n "$FALLBACK" ]; then
            echo "[*] Also found listener PID $FALLBACK — killing it."
            kill -TERM "$FALLBACK" 2>/dev/null || true
            sleep 1
            if kill -0 "$FALLBACK" 2>/dev/null; then
                kill -KILL "$FALLBACK" 2>/dev/null || true
            fi
            echo "[✓] Listener process terminated"
        fi
        return 0
    fi

    echo "[*] Stopping server (PID: $PID)..."
    kill -TERM "$PID" 2>/dev/null
    for i in {1..10}; do
        if ! kill -0 "$PID" 2>/dev/null; then
            echo "[✓] Server stopped"
            rm -f "$PID_FILE"
            return 0
        fi
        sleep 1
    done

    echo "[*] Server did not stop gracefully, forcing..."
    kill -KILL "$PID" 2>/dev/null
    rm -f "$PID_FILE"
    echo "[✓] Server killed"
    return 0
}

status_server() {
    # Fix #7: all variables are local to this function.
    local PID ORPHAN

    if [ -f "$PID_FILE" ]; then
        # Fix #6: validate PID file before use.
        if ! PID=$(read_pid_file); then
            echo "[*] Server not running (corrupt PID file removed)"
            return 1
        fi
        if kill -0 "$PID" 2>/dev/null; then
            echo "[✓] Server is running (PID: $PID)"
            echo "    Port: $DEFAULT_PORT"
            echo "    Uptime: $(ps -p "$PID" -o etime= | tr -d ' ')"
            return 0
        else
            echo "[*] Server not running (stale PID: $PID)"
            return 1
        fi
    else
        echo "[*] Server is not running"
        # Fix #1: match against $SERVER_BIN (the real binary path), not a
        # nonexistent name "mud_server".
        ORPHAN=$(pgrep -f "$SERVER_BIN" | head -1)
        if [ -n "$ORPHAN" ]; then
            echo "[*] WARNING: Found orphaned server process (PID: $ORPHAN)"
            echo "    Run: ./mud.sh stop"
        fi
        return 1
    fi
}

restart_server() {
    echo "[*] Restarting server..."
    stop_server
    sleep 2
    start_server
}

tail_log() {
    if [ -f "$LOG_FILE" ]; then
        tail -f "$LOG_FILE"
    else
        echo "[✗] No log file found at: $LOG_FILE"
        return 1
    fi
}

# --- SECTION 3: DATA MANAGEMENT COMMANDS ---

wipe_players() {
    echo "[*] Deleting player saves..."
    # Fix #5: use -- to prevent filenames beginning with "-" being parsed as flags.
    rm -rf -- "$MUDLIB_DIR/lib/save/players/"* "$MUDLIB_DIR/save/players/"* 2>/dev/null
    echo "[✓] Player saves wiped"
}

wipe_wizards() {
    echo "[*] Deleting wizard saves..."
    # Fix #5: pass -- to rm via -exec to guard against "-"-prefixed filenames.
    find "$MUDLIB_DIR/lib/save/wizard/" "$MUDLIB_DIR/save/wizard/" \
        -mindepth 1 -type f -exec rm -f -- {} + 2>/dev/null
    echo "[✓] Wizard saves wiped"
}

wipe_all() {
    # Fix #7: all variables are local to this function.
    local FORCE=0 CONFIRM
    if [[ "${1:-}" == "--force" || "${1:-}" == "-f" ]]; then
        FORCE=1
    fi
    if [ $FORCE -eq 0 ]; then
        echo "WARNING: This will delete ALL player and wizard saves."
        read -p "Type 'WIPE ALL' to confirm: " CONFIRM
        if [ "$CONFIRM" != "WIPE ALL" ]; then
            echo "[*] Wipe cancelled."
            return 1
        fi
    fi
    echo "[*] Deleting all saves..."
    # Fix #5: use -- to prevent filenames beginning with "-" being parsed as flags.
    rm -rf -- "$MUDLIB_DIR/lib/save/players/"* "$MUDLIB_DIR/save/players/"* \
              "$MUDLIB_DIR/lib/save/wizard/"*  "$MUDLIB_DIR/save/wizard/"*  2>/dev/null
    echo "[✓] All saves wiped"
}

# --- SECTION 4: CONVENIENCE COMMANDS ---

fresh() {
    # Fix #3: fresh() now accepts --force/-f to skip confirmation.
    # Without it, a clear warning and explicit prompt are shown before wiping.
    # Fix #7: all variables are local to this function.
    # Fix #8: abort on wipe or build failure instead of continuing blindly.
    local FORCE=0 CONFIRM
    if [[ "${1:-}" == "--force" || "${1:-}" == "-f" ]]; then
        FORCE=1
    fi

    echo "[*] Full reset: stop server, wipe ALL saves, rebuild driver, start server."
    if [ $FORCE -eq 0 ]; then
        echo "WARNING: This will permanently delete ALL player and wizard saves."
        read -p "Type 'YES' to confirm: " CONFIRM
        if [ "$CONFIRM" != "YES" ]; then
            echo "[*] Fresh cancelled."
            return 1
        fi
    fi

    stop_server || true
    # User already confirmed above; pass --force so wipe_all doesn't re-prompt.
    wipe_all --force    || { echo "[✗] Wipe failed, aborting.";  return 1; }
    rebuild_driver      || { echo "[✗] Build failed, aborting."; return 1; }
    start_server
}

test_connect() {
    echo "[*] Testing telnet connection to localhost:$DEFAULT_PORT..."
    if command -v telnet >/dev/null 2>&1; then
        (echo quit | telnet localhost "$DEFAULT_PORT") 2>&1 | grep -E "Connected|Escape character|Connection refused"
    else
        echo "[✗] Telnet not installed"
        return 1
    fi
}

# --- MAIN COMMAND DISPATCH ---

case "$1" in
    # Build commands
    build)
        build_driver
        ;;
    rebuild)
        rebuild_driver
        ;;
    clean)
        clean_build
        ;;
    # Runtime commands
    start)
        start_server
        ;;
    stop)
        stop_server
        ;;
    restart)
        restart_server
        ;;
    status)
        status_server
        ;;
    log|tail)
        tail_log
        ;;
    # Data management
    wipe-players)
        wipe_players
        ;;
    wipe-wizards)
        wipe_wizards
        ;;
    wipe-all)
        wipe_all "${2:-}"
        ;;
    # Convenience
    fresh)
        fresh "${2:-}"
        ;;
    test-connect)
        test_connect
        ;;
    *)
        echo "AMLP-MUD Unified Control Script"
        echo "Usage: $0 <command> [options]"
        echo ""
        echo "Build commands:"
        echo "  build             - Build driver"
        echo "  rebuild           - Clean and build driver"
        echo "  clean             - Clean build artifacts"
        echo ""
        echo "Runtime commands:"
        echo "  start             - Start the MUD server"
        echo "  stop              - Stop the MUD server"
        echo "  restart           - Restart the MUD server"
        echo "  status            - Check if server is running"
        echo "  log|tail          - Tail the server log"
        echo ""
        echo "Data management:"
        echo "  wipe-players      - Delete player saves"
        echo "  wipe-wizards      - Delete wizard saves"
        echo "  wipe-all [-f]     - Delete ALL saves (add -f to skip confirm)"
        echo ""
        echo "Convenience:"
        echo "  fresh [-f]        - Full reset: stop, wipe-all, rebuild, start"
        echo "                      (add -f to skip confirmation prompt)"
        echo "  test-connect      - Test telnet connection to server"
        exit 1
        ;;
esac
