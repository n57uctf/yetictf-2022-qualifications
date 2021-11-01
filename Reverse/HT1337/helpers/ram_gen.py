#!/usr/bin/env python3

def encrypt(data, length):
    enc_data = b""

    for i in range(0, int(length/2)):
        enc_data += (data[i] ^ 0x13).to_bytes(1, 'big')

    for i in range(int(length/2), length):
        enc_data += (data[i] ^ 0x37).to_bytes(1, 'big')

    return enc_data


data = b""

with open("flag.asci", "rb") as f:
    data = f.read()
    f.close()
length = len(data)

print(length)
enc_data = encrypt(data, length)

with open("ram.bin", "wb") as f:
    f.write(enc_data)
    for i in range(4096 - length):
        f.write(b'\x00')

    f.close()
