#!/bin/bash
# MUD Control Script

PID_FILE="logs/driver.pid"
LOG_FILE="logs/driver.log"
DRIVER_BIN="./build/driver"
if [ ! -x "$DRIVER_BIN" ]; then
    if [ -x ./driver ]; then
        DRIVER_BIN="./driver"
    else
        DRIVER_BIN=""
    fi
fi

rotate_logs() {
    echo "Rotating logs..."
    TIMESTAMP=$(date +%Y%m%d_%H%M%S)
    MAX_SIZE=$((10 * 1024 * 1024)) # 10MB

    mkdir -p logs
    for log in logs/*.log lib/log/*.log; do
        if [ -f "$log" ]; then
            SIZE=$(stat -c%s "$log" 2>/dev/null || stat -f%z "$log" 2>/dev/null || echo 0)
            if [ "$SIZE" -gt "$MAX_SIZE" ]; then
                mv "$log" "${log}.${TIMESTAMP}"
                touch "$log"
                gzip -9 "${log}.${TIMESTAMP}" &
                echo "Rotated: $log (${SIZE} bytes)"
            fi
        fi
    done

    # Clean compressed logs older than 30 days
    find logs/ -name "*.log.*.gz" -mtime +30 -delete 2>/dev/null || true
    echo "Log rotation complete"
}

case "$1" in
    start)
        if [ -f "$PID_FILE" ]; then
            echo "MUD already running (PID: $(cat $PID_FILE))"
            exit 1
        fi
        if [ -z "$DRIVER_BIN" ]; then
            echo "Driver binary not found; build first (make driver)"
            exit 1
        fi
        echo "Starting MUD..."
        nohup "$DRIVER_BIN" > "$LOG_FILE" 2>&1 &
        echo $! > "$PID_FILE"
        echo "MUD started (PID: $(cat $PID_FILE))"
        echo "Log: tail -f $LOG_FILE"
        ;;
    stop)
        if [ ! -f "$PID_FILE" ]; then
            echo "MUD not running"
            exit 1
        fi
        PID=$(cat "$PID_FILE")
        echo "Stopping MUD (PID: $PID)..."
        kill $PID || echo "Failed to kill $PID"
        rm "$PID_FILE"
        echo "MUD stopped"
        ;;
    restart)
        $0 stop
        sleep 2
        $0 start
        ;;
    status)
        if [ -f "$PID_FILE" ]; then
            PID=$(cat "$PID_FILE")
            if ps -p $PID > /dev/null; then
                echo "MUD running (PID: $PID)"
            else
                echo "MUD crashed (stale PID file)"
                rm "$PID_FILE"
            fi
        else
            echo "MUD not running"
        fi
        ;;
    tail)
        tail -f "$LOG_FILE"
        ;;
    wipe-players)
        echo "WARNING: This will DELETE all player save files!"
        read -p "Type 'YES' to confirm: " confirm
        if [ "$confirm" = "YES" ]; then
            echo "Wiping player saves..."
            find save -type f \( -name "*.o" -o -name "*.dat" \) -delete 2>/dev/null || true
            find lib/save -type f \( -name "*.o" -o -name "*.dat" \) -delete 2>/dev/null || true
            echo "Player saves wiped"
        else
            echo "Cancelled"
        fi
        ;;
    wipe-wizards)
        echo "WARNING: This will DELETE all wizard save files!"
        read -p "Type 'YES' to confirm: " confirm
        if [ "$confirm" = "YES" ]; then
            echo "Wiping wizard saves..."
            find save -type f -path "*/wizards/*" \( -name "*.o" -o -name "*.dat" \) -delete 2>/dev/null || true
            find lib/save -type f -path "*/wizards/*" \( -name "*.o" -o -name "*.dat" \) -delete 2>/dev/null || true
            echo "Wizard saves wiped"
        else
            echo "Cancelled"
        fi
        ;;
    wipe-all)
        echo "WARNING: This will DELETE ALL save files (players, wizards, rooms, workrooms)!"
        read -p "Type 'WIPE ALL' to confirm: " confirm
        if [ "$confirm" = "WIPE ALL" ]; then
            echo "Wiping all saves..."
            find save -type f \( -name "*.o" -o -name "*.dat" \) -delete 2>/dev/null || true
            find lib/save -type f \( -name "*.o" -o -name "*.dat" \) -delete 2>/dev/null || true
            rm -f data/*.dat 2>/dev/null || true
            rm -rf lib/domains/wizard/ 2>/dev/null || true
            echo "All saves wiped"
        else
            echo "Cancelled"
        fi
        ;;
    reload-lib)
        echo "Reloading library (hot reload)..."
        if [ -f "$PID_FILE" ]; then
            kill -USR1 $(cat "$PID_FILE") 2>/dev/null || echo "Signal not supported, use restart"
        else
            echo "MUD not running"
        fi
        ;;
    clean-build)
        echo "Clean rebuild and restart..."
        $0 stop || true
        make clean && make driver
        $0 start
        ;;
    build)
        echo "Building driver..."
        make driver
        ;;
    rebuild)
        echo "Rebuilding driver (clean + build)..."
        make clean && make driver
        ;;
    test-connect)
        echo "Testing telnet connection to localhost:3000..."
        (sleep 1; echo "quit") | telnet localhost 3000 || echo "telnet failed or not installed"
        ;;
    rotate-logs)
        rotate_logs
        ;;
    auto-test)
        echo "Running automated test script..."
        cat > /tmp/amlp_test.exp << 'EXPECT'
#!/usr/bin/expect -f
set timeout 5
spawn telnet localhost 3000
expect "Welcome" { send "help\r" }
expect ">" { send "who\r" }
expect ">" { send "quit\r" }
expect eof
EXPECT
        chmod +x /tmp/amlp_test.exp
        /tmp/amlp_test.exp
        ;;
    *)
        echo "Usage: $0 {start|stop|restart|status|tail|wipe-players|wipe-wizards|wipe-all|reload-lib|clean-build|build|rebuild|test-connect|auto-test|rotate-logs}"
        exit 1
        ;;
esac
