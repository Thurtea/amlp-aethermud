'use strict';

// Simple WebSocket -> Telnet proxy
// Listens for WebSocket clients and forwards text lines to a telnet server.

const WebSocket = require('ws');
const net = require('net');

const WS_PORT = process.env.WS_PORT ? parseInt(process.env.WS_PORT, 10) : 3001;
const TELNET_HOST = process.env.TELNET_HOST || '127.0.0.1';
const TELNET_PORT = process.env.TELNET_PORT ? parseInt(process.env.TELNET_PORT, 10) : 3000;

const wss = new WebSocket.Server({ port: WS_PORT });

console.log(`[proxy] WebSocket->Telnet proxy starting on ws://0.0.0.0:${WS_PORT} -> ${TELNET_HOST}:${TELNET_PORT}`);

wss.on('connection', function connection(ws, req) {
  const remote = req.socket.remoteAddress + ':' + req.socket.remotePort;
  console.log(`[proxy] WS connected: ${remote}`);

  const tcp = new net.Socket();
  let tcpOpen = false;

  tcp.connect(TELNET_PORT, TELNET_HOST, () => {
    tcpOpen = true;
    console.log(`[proxy] TCP connected to ${TELNET_HOST}:${TELNET_PORT} for ${remote}`);
  });

  tcp.on('data', (data) => {
    // Convert CRLF to LF for browser display
    let text = data.toString('utf8');
    text = text.replace(/\r\n/g, '\n');
    // Send as text frame
    if (ws.readyState === WebSocket.OPEN) {
      ws.send(text);
    }
  });

  tcp.on('close', () => {
    tcpOpen = false;
    console.log(`[proxy] TCP connection closed for ${remote}`);
    try { ws.close(); } catch (e) {}
  });

  tcp.on('error', (err) => {
    console.error(`[proxy] TCP error for ${remote}:`, err.message);
    try { ws.send(`[proxy] TCP error: ${err.message}\n`); } catch (e) {}
  });

  ws.on('message', (message) => {
    // Accept Buffer or string
    let text = (typeof message === 'string') ? message : message.toString('utf8');

    // Ensure newline at end so telnet server processes line-oriented input
    if (!text.endsWith('\n')) text += '\n';

    if (tcpOpen) {
      tcp.write(text);
    } else {
      ws.send('[proxy] Not connected to telnet server\n');
    }
  });

  ws.on('close', (code, reason) => {
    console.log(`[proxy] WS closed ${remote} (${code})`);
    if (tcpOpen) tcp.end();
  });

  ws.on('error', (err) => {
    console.error(`[proxy] WS error ${remote}:`, err.message);
    if (tcpOpen) tcp.destroy();
  });
});

wss.on('listening', () => {
  console.log('[proxy] WebSocket server listening');
});

wss.on('error', (err) => {
  console.error('[proxy] WebSocket server error:', err.message);
});
