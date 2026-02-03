#!/usr/bin/env python3
"""Test script for verifying command output routing"""

import socket
import time
import sys

def main():
    print("=== Testing AMLP Command Output Routing ===\n")
    
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(3.0)
        print("Connecting to localhost:3000...")
        sock.connect(('localhost', 3000))
        print("Connected!\n")
        
        # Read welcome banner
        time.sleep(0.5)
        try:
            welcome = sock.recv(8192).decode('utf-8', errors='ignore')
            print("=== Welcome Banner ===")
            print(welcome)
            print("=" * 50)
        except socket.timeout:
            print("(No welcome banner received)")
        
        # Send username
        print("\n>>> Sending: admin")
        sock.sendall(b"admin\n")
        time.sleep(1.0)
        
        try:
            response = sock.recv(8192).decode('utf-8', errors='ignore')
            print("<<< Response:")
            print(response)
        except socket.timeout:
            print("(No response)")
        
        # Send password
        print("\n>>> Sending: admin123")
        sock.sendall(b"admin123\n")
        time.sleep(2.0)
        
        try:
            response = sock.recv(8192).decode('utf-8', errors='ignore')
            print("<<< Response:")
            print(response)
        except socket.timeout:
            print("(No response)")
        
        # Try look command
        print("\n>>> Sending: look")
        sock.sendall(b"look\n")
        time.sleep(1.0)
        
        try:
            response = sock.recv(8192).decode('utf-8', errors='ignore')
            print("<<< Response:")
            print(response)
        except socket.timeout:
            print("(No response)")
        
        # Quit
        print("\n>>> Sending: quit")
        sock.sendall(b"quit\n")
        time.sleep(0.5)
        
        sock.close()
        print("\n=== Test Complete ===")
        
    except Exception as e:
        print(f"ERROR: {e}")
        import traceback
        traceback.print_exc()
        return 1
    
    return 0

if __name__ == "__main__":
    sys.exit(main())
