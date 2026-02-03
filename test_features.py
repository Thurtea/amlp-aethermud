#!/usr/bin/env python3
"""Test AMLP server features"""

import socket
import time
import sys

def send_and_wait(sock, msg, wait=0.5):
    """Send message and wait for response"""
    if msg:
        sock.sendall((msg + "\n").encode())
    time.sleep(wait)
    try:
        sock.settimeout(wait)
        data = sock.recv(4096).decode('utf-8', errors='ignore')
        return data
    except socket.timeout:
        return ""

def test_character_creation():
    """Test creating a character and checking features"""
    print("Connecting to server...")
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('localhost', 3000))
    
    # Read welcome
    time.sleep(1)
    data = sock.recv(4096).decode()
    print("=== WELCOME ===")
    print(data)
    
    # Create character
    print("\n=== CREATING CHARACTER ===")
    sock.sendall(b"testchar2\n")
    time.sleep(1)
    data = sock.recv(4096).decode()
    print(data)
    
    # Password
    sock.sendall(b"test123\n")
    time.sleep(0.5)
    data = sock.recv(4096).decode()
    print(data)
    
    # Confirm password
    sock.sendall(b"test123\n")
    time.sleep(1)
    data = sock.recv(4096).decode()
    print(data)
    
    # Race selection (1 = Human)
    sock.sendall(b"1\n")
    time.sleep(0.5)
    data = sock.recv(4096).decode()
    print(data)
    
    # Confirm race
    sock.sendall(b"y\n")
    time.sleep(0.5)
    data = sock.recv(4096).decode()
    print(data)
    
    # Gender
    sock.sendall(b"m\n")
    time.sleep(1)
    data = sock.recv(4096).decode()
    print(data)
    
    # OCC selection (1 = first one)
    sock.sendall(b"1\n")
    time.sleep(0.5)
    data = sock.recv(4096).decode()
    print(data)
    
    # Confirm OCC
    sock.sendall(b"y\n")
    time.sleep(1)
    data = sock.recv(4096).decode()
    print(data)
    
    # Roll stats (press enter twice then accept)
    sock.sendall(b"\n")
    time.sleep(0.5)
    data = sock.recv(4096).decode()
    print(data)
    
    sock.sendall(b"\n")
    time.sleep(0.5)
    data = sock.recv(4096).decode()
    print(data)
    
    sock.sendall(b"y\n")
    time.sleep(0.5)
    data = sock.recv(4096).decode()
    print(data)
    
    # Alignment (default)
    sock.sendall(b"\n")
    time.sleep(0.5)
    data = sock.recv(4096).decode()
    print(data)
    
    # Finish creation
    sock.sendall(b"\n")
    time.sleep(2)
    data = sock.recv(4096).decode()
    print("\n=== CHARACTER CREATED ===")
    print(data)
    
    # Test look command
    print("\n=== TESTING LOOK COMMAND (EXIT DISPLAY) ===")
    sock.sendall(b"look\n")
    time.sleep(1)
    data = sock.recv(4096).decode()
    print(data)
    
    # Check if exits are bold green
    if "\033[1;32m" in data:
        print("✓ Exit display uses ANSI colors")
    else:
        print("✗ Exit display missing ANSI colors")
    
    # Test inventory
    print("\n=== TESTING INVENTORY (STARTING EQUIPMENT) ===")
    sock.sendall(b"inventory\n")
    time.sleep(1)
    data = sock.recv(4096).decode()
    print(data)
    
    # Test score
    print("\n=== TESTING SCORE (SKILLS/ABILITIES) ===")
    sock.sendall(b"score\n")
    time.sleep(1)
    data = sock.recv(4096).decode()
    print(data)
    
    # Quit
    print("\n=== QUITTING ===")
    sock.sendall(b"quit\n")
    time.sleep(0.5)
    
    sock.close()
    print("\n=== TEST COMPLETE ===")

if __name__ == "__main__":
    try:
        test_character_creation()
    except Exception as e:
        print(f"Error:  {e}")
        sys.exit(1)
