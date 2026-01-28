#!/usr/bin/env python3
"""
Async WebSocket -> Telnet proxy for AMLP driver

Usage:
  pip install websockets
  python3 proxy.py [--ws-port 3001] [--telnet-host 127.0.0.1] [--telnet-port 3000]

Default: ws://0.0.0.0:3001 -> 127.0.0.1:3000

This proxy forwards text frames (UTF-8) from WebSocket clients to the telnet server
and forwards telnet server output back to the WebSocket client as text frames.
"""

import asyncio
import argparse
import logging

import websockets

logging.basicConfig(level=logging.INFO, format='[proxy] %(message)s')

async def handle_client(ws, path, telnet_host, telnet_port):
    peer = ws.remote_address
    logging.info(f"WS connected: {peer}")

    try:
        reader, writer = await asyncio.open_connection(telnet_host, telnet_port)
        logging.info(f"TCP connected to {telnet_host}:{telnet_port} for {peer}")
    except Exception as e:
        logging.error(f"TCP connect error: {e}")
        await ws.send(f"[proxy] TCP connect error: {e}\n")
        await ws.close()
        return

    async def tcp_to_ws():
        try:
            while True:
                data = await reader.read(4096)
                if not data:
                    logging.info(f"TCP closed by server for {peer}")
                    await ws.close()
                    break
                # Normalize CRLF -> LF so browser displays correctly
                text = data.decode('utf-8', errors='replace').replace('\r\n', '\n')
                await ws.send(text)
        except (asyncio.CancelledError, websockets.ConnectionClosed):
            pass
        except Exception as e:
            logging.error(f"tcp_to_ws error: {e}")

    async def ws_to_tcp():
        try:
            async for message in ws:
                # websockets lib gives str for text frames, bytes for binary
                if isinstance(message, str):
                    text = message
                else:
                    text = message.decode('utf-8', errors='replace')

                # Ensure newline so telnet server processes the line
                if not text.endswith('\n'):
                    text = text + '\n'
                writer.write(text.encode('utf-8'))
                await writer.drain()
        except (asyncio.CancelledError, websockets.ConnectionClosed):
            pass
        except Exception as e:
            logging.error(f"ws_to_tcp error: {e}")

    tcp_task = asyncio.create_task(tcp_to_ws())
    ws_task = asyncio.create_task(ws_to_tcp())

    done, pending = await asyncio.wait([tcp_task, ws_task], return_when=asyncio.FIRST_COMPLETED)

    for p in pending:
        p.cancel()

    try:
        writer.close()
        await writer.wait_closed()
    except Exception:
        pass

    try:
        await ws.close()
    except Exception:
        pass

    logging.info(f"Connection closed: {peer}")


async def main(ws_port, telnet_host, telnet_port):
    server = await websockets.serve(lambda ws, path: handle_client(ws, path, telnet_host, telnet_port), '0.0.0.0', ws_port)
    logging.info(f"WebSocket->Telnet proxy listening on ws://0.0.0.0:{ws_port} -> {telnet_host}:{telnet_port}")
    await server.wait_closed()


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--ws-port', type=int, default=3001)
    parser.add_argument('--telnet-host', default='127.0.0.1')
    parser.add_argument('--telnet-port', type=int, default=3000)
    args = parser.parse_args()

    try:
        asyncio.run(main(args.ws_port, args.telnet_host, args.telnet_port))
    except KeyboardInterrupt:
        logging.info('Shutting down')
