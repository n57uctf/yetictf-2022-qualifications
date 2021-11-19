#!/usr/bin/env python3

import sys

if len(sys.argv) != 2:
    print("Usage: decode <path>")
    exit(0)

fname = str(sys.argv[1])

with open(fname, "rb") as f:
    data = f.read()

i = 0

while(True):
    n = 0

    # JMP address
    if ((data[i] & 0b11111000) == 0b11100000):
        n = ((n & 0b0111 ) << 8) | data[i + 1]
        print(str(i) + "  JMP " + str(n))
        i += 2

    # JNZ address
    elif ((data[i] & 0b11111000) == 0b10111000):
        n = ((n & 0b0111 ) << 8) | data[i + 1]
        print(str(i) + "  JNZ " + str(n))
        i += 2

    # JZ address
    elif ((data[i] & 0b11110000) == 0b10110000):
        n = ((n & 0b0111 ) << 8) | data[i + 1]
        print(str(i) + "  JZ " + str(n))
        i += 2

    elif ((data[i] == 0b01000010)):
        n = (data[i + 1] << 8) | data[i + 2]
        print(str(i) + "  ADN A," + str(n))
        i += 3

    elif ((data[i] == 0b00101100)):
        n = (data[i + 1] & 0b0111)
        print(str(i) + "  MOV R" + str(n) + ",A")
        i += 2

    elif ((data[i] == 0b01110000)):
        n = (data[i + 1] << 8) | data[i + 2]
        print(str(i) + "  MOV A, " + str(n))
        i += 3

    elif ((data[i] == 0b00111000)):
        n = (data[i + 1] | 0b0111)
        print(str(i) + "  DEC R" + str(n))
        i += 2

    elif ((data[i] == 0b01110000)):
        n = (data[i + 1] << 8) | data[i + 2]
        print(str(i) + "  MOV A, " + str(n))
        i += 3

    elif ((data[i] == 0b01000011)):
        n = (data[i + 1] << 8) | data[i + 2]
        print(str(i) + "  XOR A, " + str(n))
        i += 3

    elif ((data[i] == 0b00011000)):
        n = (data[i + 1] & 0b0111)
        print(str(i) + "  INC R" + str(n))
        i += 2

    elif ((data[i] == 0b00101101)):
        n = (data[i + 1]  & 0b111)
        print(str(i) + "  MOV A, R" + str(n))
        i += 2

    elif ((data[i] == 0b00000100)):
        print(str(i) + "  MOV A, [R1R0]")
        i += 1

    elif ((data[i] == 0b00000101)):
        print(str(i) + "  MOV [R1R0], A" + str(n))
        i += 1

    elif ((data[i] == 0b00101110)):
        print(str(i) + "  RET")
        exit(0)

    else:
        print("WTF")
        exit(0)
