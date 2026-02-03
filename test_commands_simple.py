#!/usr/bin/env python3
"""Simple test for command output - uses expect-style delays"""

import socket
import time
import sys

HOST = 'localhost'
PORT = 3000

def main():
    print("=== Testing Command Output ===\n")
    
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((HOST, PORT))
    sock.settimeout(1.0)
    
    def send(text):
        print(f">>> {text}")
        sock.sendall((text + "\n").encode())
        time.sleep(0.5)
    
    def receive():
        try:
            data = sock.recv(8192).decode('utf-8', errors='ignore')
            if data:
                print(data, end='')
            return data
        except socket.timeout:
            return ""
    
    # Get banner
    time.sleep(0.5)
    receive()
    
    # Login
    send("quicktest")
    receive()
    
    send("password123")
    receive()
    
    send("password123")
    receive()
    
    # Race selection
    send("1")
    time.sleep(1.0)
    stats = receive()
    
    # Accept stats
    if "Accept" in stats:
        send("yes")
        time.sleep(1.0)
        receive()
    
    print("\n" + "="*60)
    print("NOW TESTING IN-GAME COMMANDS")
    print("="*60 + "\n")
    
    # Test commands
    commands = ["look", "inventory", "score", "help", "who"]
    
    for cmd in commands:
        print(f"\n>>> Testing: {cmd}")
        send(cmd)
        time.sleep(0.8)
        output = receive()
        
        if output.strip():
            print(f"✓ GOT OUTPUT ({len(output)} bytes)")
        else:
            print(f"✗ NO OUTPUT")
    
    send("quit")
    sock.close()
    
    print("\n=== Test Complete ===")

if __name__ == "__main__":
    main()
