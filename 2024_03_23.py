import socket
import select
import struct
import sys
import time
import os

# ---configurations---
HOST = '123.123.123.123'
PORT = 12345
FD = 0
# --------------------

def send_message(sock, message):
    length = len(message)
    sock.sendall(struct.pack('!I', length) + message)
    if length > 0:
        print(f"Sent: {message.decode()}")
    else:
        print("Send: ping")

def can_read_from(sock):
    readable, _, _ = select.select([sock], [], [], 0.1)
    return sock in readable

def receive_message(sock, length):
    message = b''
    while len(message) < length:
        if can_read_from(sock):
            part = sock.recv(length - len(message))
            message += part
    return message

def receive_length(sock):
    length = receive_message(sock, 4)
    return struct.unpack('!I', length)[0]

def handshake(sock):
    sock.sendall(b"HELLO")
    sock.settimeout(3)
    response = receive_message(sock, 5).decode()
    if response == 'WORLD':
        print("Handshake successful.")
        return True
    else:
        print("Handshake failed.")
        return False

def main(host, port, fd):
    forward = fd >= 0

    # connect to the server
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((host, port))

    # discard message before handshake
    if forward:
        while True:
            if can_read_from(fd):
                data = os.read(fd, 1024)
            else:
                break

    # handshake
    suc = handshake(sock)
    if not suc:
        exit(1)

    # start
    last_ping_time = 0
    recv_pong_time = 0
    sock.setblocking(False)
    while True:
        current_time = time.time()
        if current_time - recv_pong_time > 4 and last_ping_time <= recv_pong_time:
            send_message(sock, b'')
            last_ping_time = current_time

        if current_time - last_ping_time > 5 and recv_pong_time <= last_ping_time:
            sock.close()
            break

        if can_read_from(sock):
            N = receive_length(sock)

            if N == 0:
                print("Received: pong")
                recv_pong_time = current_time
            else:
                message = receive_message(sock, N)
                print(f"Received: {message.decode()}")
                send_message(sock, message[::-1])

        if forward:
            if can_read_from(fd):
                data = os.read(fd, 1024).replace(b'\n', b'')
                send_message(sock, data)

if __name__ == "__main__":
    while True:
        main(HOST, PORT, FD)
        time.sleep(5)
