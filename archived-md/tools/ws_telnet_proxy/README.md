# AMLP WebSocket → Telnet Proxy

This small proxy accepts WebSocket connections and forwards newline-terminated text to a telnet server (the AMLP driver). It is intended as a non-invasive bridge so browser-based clients can connect to the telnet-only driver.

Defaults
- WebSocket listen: `ws://0.0.0.0:3001`
- Telnet target: `127.0.0.1:3000`

Environment variables
- `WS_PORT` - port for WebSocket server (default 3001)
- `TELNET_HOST` - telnet destination host (default 127.0.0.1)
- `TELNET_PORT` - telnet destination port (default 3000)

Install and run

```bash
cd tools/ws_telnet_proxy
npm install
npm start
```

Quick test with `wscat` (install with `npm i -g wscat`)

```bash
wscat -c ws://localhost:3001
# then type: look
# and you should see responses from the MUD server (if running on port 3000)
```

Notes
- The proxy sends and receives plain UTF-8 text frames.
- It ensures lines end with `\n` when forwarding to the telnet server.
- TCP data `\r\n` is normalized to `\n` before sending to the browser.

Python proxy
--------------
You can run the bundled Python asyncio proxy (no Node required). Install the dependency and run:

```bash
cd tools/ws_telnet_proxy
python3 -m pip install --user websockets
python3 proxy.py --ws-port 3001 --telnet-host 127.0.0.1 --telnet-port 3000
```

The Python proxy behaves similarly to the Node proxy: it accepts WebSocket text frames and forwards newline-terminated text to the telnet server.
