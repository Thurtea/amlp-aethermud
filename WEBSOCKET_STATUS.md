# AMLP Driver WebSocket Implementation Status

**Date:** January 28, 2026  
**Status:** WebSocket library implemented but NOT integrated into server yet

## CRITICAL INFORMATION

⚠️ **The amlp-driver currently does NOT have an active WebSocket server.**

- **What exists:** WebSocket protocol implementation in `src/websocket.c` and `src/websocket.h`
- **What's missing:** Integration into the actual server (`src/server.c`)
- **Current server:** Pure telnet server on port **3000** (not WebSocket)
- **Client expectation:** `ws_client.html` tries to connect to `ws://localhost:3001`

## Detailed Answers to Questions

### 1) Listening address

**Current Status:**
- **NO WebSocket server is running**
- Telnet server runs on `0.0.0.0:3000` (configurable via command line)
- The HTML client expects `ws://localhost:3001` but nothing is listening there

**Code References:**
- [src/server.c](src/server.c#L36): `#define DEFAULT_PORT 3000`
- Server accepts: `./build/driver [port] [master_path]`
- TLS/wss: **NOT supported**

**What needs to be done:**
- Create separate WebSocket server or add WebSocket upgrade handling to existing server
- Choose port (3001 suggested by client, or reuse 3000 with upgrade detection)

### 2) Subprotocols / headers

**Implementation Details:**
- [src/websocket.c:276](src/websocket.c#L276): Optionally handles `Sec-WebSocket-Protocol` header
- [src/websocket.c:267](src/websocket.c#L267): Requires `Sec-WebSocket-Key` for handshake
- Standard RFC 6455 WebSocket handshake
- **No custom headers required**

**Example from code:**
```c
char *protocol = find_header_value(request, "Sec-WebSocket-Protocol");
```

### 3) Message framing & encoding

**From websocket.h/websocket.c:**
- Uses **text frames** (`WS_OPCODE_TEXT = 0x1`)
- **UTF-8 encoding** (standard WebSocket text)
- Each WebSocket message is a complete logical message (not line-oriented in framing)
- However, server logic expects **newline-delimited commands** internally

**Code References:**
- [src/websocket.h:26](src/websocket.h#L26): `#define WS_OPCODE_TEXT 0x1`
- [src/websocket.c:448](src/websocket.c#L448): `ws_encode_text()` creates text frames

### 4) Message formats

**Current Server (Telnet):**
- **Format:** Plain text, CRLF line-terminated (`\r\n`)
- **No JSON** - raw command strings

**Example Server->Client:**
```
Welcome to the AMLP MUD!\r\n
\r\n
Enter your name: 
```

**Example Client->Server:**
```
look\n
say Hello world\n
quit\n
```

**ANSI Codes:**
- Server does NOT currently send ANSI color codes
- WebSocket library has ANSI converter: [src/websocket.c:533](src/websocket.c#L533) `ws_convert_ansi()`
  - Mode 0: Strip ANSI
  - Mode 1: Convert to HTML `<span>` tags

### 5) Client input expectations

**Expected Format:**
- Send command as plain text with newline: `"look\n"` or `"look\r\n"`
- **NOT** JSON wrapped
- Server processes line-by-line: [src/server.c:718-736](src/server.c#L718)

**Line Processing:**
```c
while ((newline = strchr(line_start, '\n')) != NULL) {
    *newline = '\0';
    // Strip \r
    char *cr = strchr(line_start, '\r');
    if (cr) *cr = '\0';
    // Process command
}
```

### 6) Telnet/terminal specifics

**Current Implementation:**
- **NO Telnet IAC negotiation** in WebSocket code
- Telnet server uses CRLF (`\r\n`) line endings
- **NO ANSI codes currently sent** (but library can handle conversion)
- WebSocket can normalize line endings: [src/websocket.c:583](src/websocket.c#L583)

### 7) Heartbeat / keepalive

**Implemented in Library:**
- Supports WebSocket **PING/PONG** frames (RFC 6455)
- [src/websocket.h:29](src/websocket.h#L29): `WS_OPCODE_PING = 0x9`, `WS_OPCODE_PONG = 0xA`
- [src/websocket.c:472](src/websocket.c#L472): `ws_encode_pong()` creates pong responses

**What's needed:**
- Server must respond to PING frames with PONG
- No application-level heartbeat currently

### 8) Connection lifecycle & errors

**WebSocket Close Codes (Defined):**
- [src/websocket.h:33-37](src/websocket.h#L33):
  - `WS_CLOSE_NORMAL = 1000`
  - `WS_CLOSE_GOING_AWAY = 1001`
  - `WS_CLOSE_PROTOCOL_ERROR = 1002`
  - `WS_CLOSE_INVALID_DATA = 1003`
  - `WS_CLOSE_TOO_LARGE = 1009`

**Server Messages:**
- "Server full." - When max clients reached
- "You have been idle too long. Disconnecting..." - After 30 min idle
- "Goodbye, [name]!" - On quit command

### 9) Authentication / handshake

**Login Flow (from server.c):**
1. Connect → Welcome banner displayed
2. Enter username (3-15 chars)
3. First player → Set password (becomes **Admin**)
4. Subsequent players → Set password (regular **Player**)
5. Playing state → Can enter commands

**No tokens** - Simple username/password at connection

**First Player Special:**
```c
if (!first_player_created) {
    session->privilege_level = 2;  /* Admin */
    first_player_created = 1;
}
```

### 10) Binary or file transfer

**Current Status:**
- **NO binary transfer** implemented
- WebSocket library supports binary opcode: `WS_OPCODE_BINARY = 0x2`
- Not used by current MUD server

### 11) Limits & fragmentation

**Defined Limits:**
- [src/websocket.h:40](src/websocket.h#L40): `#define WS_MAX_FRAME_SIZE 65536` (64 KB)
- [src/websocket.h:41](src/websocket.h#L41): `#define WS_MAX_HEADER_SIZE 14`
- Server buffer: `#define BUFFER_SIZE 4096`

**Fragmentation:**
- Library tracks FIN bit: [src/websocket.c:343](src/websocket.c#L343)
- **Continuation frames supported** but not fully tested

### 12) Code pointers

**WebSocket Library:**
- [src/websocket.h](src/websocket.h) - Header with all API functions
- [src/websocket.c](src/websocket.c) - Implementation
  - Line 240: `ws_is_upgrade_request()` - Detects WebSocket handshake
  - Line 256: `ws_handle_handshake()` - Generates HTTP 101 response
  - Line 334: `ws_decode_frame()` - Parses incoming frames
  - Line 407: `ws_encode_frame()` - Creates outgoing frames
  - Line 448: `ws_encode_text()` - Convenience for text messages
  - Line 533: `ws_convert_ansi()` - ANSI to HTML conversion

**Server (Currently Telnet Only):**
- [src/server.c](src/server.c) - Main server loop
  - Line 36: Port configuration (3000)
  - Line 718: `handle_session_input()` - Processes commands
  - Line 214: `execute_command()` - Command dispatcher

**Build:**
- [Makefile:20](Makefile#L20) - Links `websocket.c`

### 13) Build/run details

**Build:**
```bash
cd /home/thurtea/amlp-driver
make clean && make all
```

**Run Telnet Server:**
```bash
# Default port 3000
./build/driver

# Custom port
./build/driver 4000

# Custom port + master path
./build/driver 4000 lib/secure/master.c
```

**Config File:**
- [config/runtime.conf](config/runtime.conf) - Has `PORT=4000` but NOT used by code
- Port must be passed as command-line arg

**Environment Variables:**
- None currently supported

### 14) Examples & tests

**Current Tests:**
- NO WebSocket integration tests exist
- Could write test connecting to WebSocket server

**Manual Test (Once Integrated):**
```bash
# Install wscat
npm install -g wscat

# Connect
wscat -c ws://localhost:3001

# Send commands
> look
> say Hello
> quit
```

**Browser Test:**
1. Open `tools/ws_client.html` in browser
2. Click "Connect"
3. Type commands and press Enter

### 15) Anything else

**Key Issues:**
1. **WebSocket server not running** - Library implemented but not integrated
2. **Port mismatch** - Client expects 3001, telnet uses 3000
3. **Line ending handling** - Telnet uses `\r\n`, web likely sends `\n`
4. **Buffer handling** - Need to accumulate WebSocket messages properly

**Protocol Quirks:**
- Server expects newline-terminated commands
- First player gets admin automatically
- Session timeout: 30 minutes idle
- Max clients: 100

---

## What You Need to Tell Copilot

**Copy-paste this to the other workspace:**

```
CRITICAL: The amlp-driver WebSocket library is fully implemented but NOT integrated into the server yet.

CURRENT STATE:
- WebSocket protocol library: COMPLETE (src/websocket.c, src/websocket.h)
- WebSocket server: NOT RUNNING
- Active server: Telnet-only on port 3000
- Client HTML expects: ws://localhost:3001 (nothing listening)

TO IMPLEMENT WEBSOCKET SERVER:
1. Create new server or add upgrade detection to src/server.c
2. Detect HTTP GET with "Upgrade: websocket" header
3. Call ws_handle_handshake() to complete upgrade
4. Use ws_decode_frame() for incoming data
5. Use ws_encode_text() for outgoing data
6. Handle PING/PONG frames for keepalive

PROTOCOL DETAILS:
- Format: Plain text commands (NOT JSON)
- Encoding: UTF-8
- Line-oriented: Each command ends with \n or \r\n
- Example client->server: "look\n", "say Hello\n", "quit\n"
- Example server->client: "You are in the starting room.\r\n> "

MESSAGE FLOW:
Client -> WebSocket frame -> Decoded payload -> Line buffer -> Command parser -> Response -> Encoded frame -> Client

KEY FUNCTIONS (all in src/websocket.c):
- ws_is_upgrade_request(data, len) - Returns 1 if HTTP upgrade
- ws_handle_handshake(request, len, &result) - Returns HTTP 101 response
- ws_decode_frame(data, len, &frame, &consumed) - Returns decoded frame
- ws_encode_text(text, &out_len) - Returns WebSocket text frame
- ws_encode_pong(payload, len, &out_len) - Returns pong response
- ws_frame_free(&frame) - Cleanup

LIMITS:
- Max frame size: 65536 bytes
- Max clients: 100
- Session timeout: 1800 seconds (30 min)
- Input buffer: 2048 bytes

AUTHENTICATION:
- No tokens or initial handshake required
- After WebSocket connect, server sends welcome banner automatically
- Client responds with username when prompted
- First player becomes Admin (privilege level 2)

NO SUPPORT FOR:
- TLS/wss
- Binary frames (only text)
- Telnet IAC negotiation
- ANSI color codes (but can convert with ws_convert_ansi())
- JSON protocol (plain text only)

FILES TO INTEGRATE:
- src/websocket.h - API declarations
- src/websocket.c - Implementation (SHA-1, Base64, frame encoding/decoding)
- src/server.c - Add WebSocket detection and handling here

SUGGESTED IMPLEMENTATION:
1. In server select() loop, detect if incoming data starts with "GET "
2. Call ws_is_upgrade_request() to verify WebSocket upgrade
3. Call ws_handle_handshake() to get HTTP 101 response
4. Mark connection as WebSocket mode
5. For WebSocket connections:
   - Read data -> ws_decode_frame() -> extract payload
   - Handle PING (opcode 0x9) -> ws_encode_pong()
   - Handle TEXT (opcode 0x1) -> process as command
   - Handle CLOSE (opcode 0x8) -> close connection
6. For sending to WebSocket clients:
   - ws_encode_text(message, &len) -> send() encoded frame

EXAMPLE INTEGRATION PATTERN:
```c
// In accept() handler
if (ws_is_upgrade_request(buffer, bytes)) {
    WSHandshake hs;
    ws_handle_handshake(buffer, bytes, &hs);
    send(fd, hs.response, hs.response_len, 0);
    ws_handshake_free(&hs);
    session->is_websocket = 1;  // Mark as WS
}

// In read() handler for WebSocket connections
WSFrame frame;
size_t consumed;
if (ws_decode_frame(buffer, bytes, &frame, &consumed) == 0) {
    if (frame.opcode == WS_OPCODE_TEXT) {
        process_command(frame.payload);
    } else if (frame.opcode == WS_OPCODE_PING) {
        size_t pong_len;
        uint8_t *pong = ws_encode_pong(frame.payload, frame.payload_len, &pong_len);
        send(fd, pong, pong_len, 0);
        free(pong);
    }
    ws_frame_free(&frame);
}

// In send to client
size_t frame_len;
uint8_t *frame = ws_encode_text("You are here.\r\n", &frame_len);
send(fd, frame, frame_len, 0);
free(frame);
```

See attached files ws_client.html, websocket.c, websocket.h for full implementation.
```

---

## Raw Code Excerpts

### websocket.h (Key Definitions)

```c
#define WS_OPCODE_TEXT          0x1
#define WS_OPCODE_CLOSE         0x8
#define WS_OPCODE_PING          0x9
#define WS_OPCODE_PONG          0xA

#define WS_MAX_FRAME_SIZE       65536

typedef struct {
    int fin;
    int opcode;
    int masked;
    uint64_t payload_len;
    uint8_t mask_key[4];
    uint8_t *payload;
} WSFrame;

int ws_is_upgrade_request(const char *data, size_t len);
int ws_handle_handshake(const char *request, size_t request_len, WSHandshake *result);
int ws_decode_frame(const uint8_t *data, size_t data_len, WSFrame *frame, size_t *consumed);
uint8_t *ws_encode_text(const char *text, size_t *output_len);
uint8_t *ws_encode_pong(const uint8_t *ping_payload, size_t payload_len, size_t *output_len);
void ws_frame_free(WSFrame *frame);
```

### Example Message Exchange

**Connect:**
```
Client: GET / HTTP/1.1
Client: Upgrade: websocket
Client: Connection: Upgrade
Client: Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==

Server: HTTP/1.1 101 Switching Protocols
Server: Upgrade: websocket
Server: Connection: Upgrade
Server: Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo=
```

**Server Welcome:**
```
[WebSocket Text Frame]
Welcome to the AMLP MUD!\r\n
\r\n
Enter your name: 
```

**Client Command:**
```
[WebSocket Text Frame]
look\n
```

**Server Response:**
```
[WebSocket Text Frame]
You are in the starting room.\r\n
This is a simple test environment for the AMLP driver.\r\n
Obvious exits: none yet\r\n
\r\n
> 
```

**Heartbeat:**
```
Client: [PING frame with empty payload]
Server: [PONG frame echoing payload]
```

**Disconnect:**
```
Client: quit\n
Server: Goodbye, playername!\r\n
Server: [CLOSE frame, code 1000]
```
