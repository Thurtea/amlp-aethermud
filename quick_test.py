#!/usr/bin/env python3
"""Quick test to see exit display"""

import socket
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('localhost', 3000))

# Read welcome
time.sleep(1)
data = sock.recv(4096).decode()
print(data)

# Send username
sock.sendall(b"quicktest\n")
time.sleep(1)
data = sock.recv(4096).decode()
print(data)

# New password
sock.sendall(b"test123\n")
time.sleep(0.5)
data = sock.recv(4096).decode()
print(data)

# Confirm password
sock.sendall(b"test123\n")
time.sleep(1)
data = sock.recv(4096).decode()
print(data)

# Race (1 = Human)
sock.sendall(b"1\n")
time.sleep(0.5)
data = sock.recv(4096).decode()
print(data)

# Confirm
sock.sendall(b"y\n")
time.sleep(0.5)
data = sock.recv(4096).decode()
print(data)

# Gender
sock.sendall(b"m\n")
time.sleep(1)
data = sock.recv(4096).decode()
print(data)

# OCC
sock.sendall(b"1\n")
time.sleep(0.5)
data = sock.recv(4096).decode()
print(data)

# Confirm
sock.sendall(b"y\n")
time.sleep(1)
data = sock.recv(4096).decode()
print(data)

# Roll stats
sock.sendall(b"\n")
time.sleep(0.5)
data = sock.recv(4096).decode()
print(data)

sock.sendall(b"\n")
time.sleep(0.5)
data = sock.recv(4096).decode()
print(data)

# Accept
sock.sendall(b"y\n")
time.sleep(0.5)
data = sock.recv(4096).decode()
print(data)

# Alignment
sock.sendall(b"\n")
time.sleep(0.5)
data = sock.recv(4096).decode()
print(data)

# Finish
sock.sendall(b"\n")
time.sleep(2)
data = sock.recv(4096).decode()
print("\n=== FINAL OUTPUT WITH EXIT DISPLAY ===")
print(data)
print("=== END ===")

# Quit
sock.sendall(b"quit\n")
time.sleep(0.5)

sock.close()
