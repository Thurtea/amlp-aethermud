#!/usr/bin/env python3
"""Complete test for command output routing"""

import socket
import time

def send_line(sock, text):
    """Send a line and wait"""
    print(f">>> {text}")
    sock.sendall((text + "\n").encode())
    time.sleep(0.3)

def recv_all(sock, timeout=2.0):
    """Receive all available data"""
    sock.settimeout(timeout)
    chunks = []
    try:
        while True:
            chunk = sock.recv(4096).decode('utf-8', errors='ignore')
            if not chunk:
                break
            chunks.append(chunk)
    except socket.timeout:
        pass
    return ''.join(chunks)

def main():
    print("=== Testing Command Output Routing ===\n")
    
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('localhost', 3000))
    
    # Get welcome
    print(recv_all(sock, 1.0))
    
    # Create new character
    send_line(sock, "testbot")
    print(recv_all(sock, 0.5))
    
    send_line(sock, "password123")
    print(recv_all(sock, 0.5))
    
    send_line(sock, "password123")
    time.sleep(1.0)
    chargen_output = recv_all(sock, 0.5)
    print(chargen_output)
    
    # Skip through chargen (race/occ selection)
    if "race" in chargen_output.lower() or "select" in chargen_output.lower():
        # Select race (Human = 1)
        send_line(sock, "1")
        time.sleep(0.8)
        stats_output = recv_all(sock, 0.5)
        print(stats_output)
        
        # Accept stats (type "yes")
        if "accept" in stats_output.lower() or "reroll" in stats_output.lower():
            send_line(sock, "yes")
            time.sleep(1.0)
            welcome_output = recv_all(sock, 0.5)
            print(welcome_output)
    
    # Now we should be in game - test commands
    print("\n" + "="*50)
    print("TESTING COMMANDS")
    print("="*50 + "\n")
    
    send_line(sock, "look")
    time.sleep(0.5)
    look_output = recv_all(sock, 0.5)
    print(f"<<< LOOK OUTPUT:\n{look_output}\n")
    
    send_line(sock, "inventory")
    time.sleep(0.5)
    inv_output = recv_all(sock, 0.5)
    print(f"<<< INVENTORY OUTPUT:\n{inv_output}\n")
    
    send_line(sock, "score")
    time.sleep(0.5)
    score_output = recv_all(sock, 0.5)
    print(f"<<< SCORE OUTPUT:\n{score_output}\n")
    
    send_line(sock, "help")
    time.sleep(0.5)
    help_output = recv_all(sock, 0.5)
    print(f"<<< HELP OUTPUT:\n{help_output}\n")
    
    # Check if we got any output
    if look_output.strip() or inv_output.strip() or score_output.strip() or help_output.strip():
        print("\n✓ SUCCESS: Commands are producing output!")
    else:
        print("\n✗ FAILED: Commands produced no output")
    
    send_line(sock, "quit")
    sock.close()

if __name__ == "__main__":
    main()
