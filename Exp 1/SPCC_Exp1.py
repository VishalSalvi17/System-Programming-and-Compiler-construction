#Name = Vishal Salvi
#UID = 2019230069
#Roll No = 52
# Experiment no 1
#Aim = To implement two pass assembler

import math
import re

opcode = {
    'STL': '14',
    'JSUB': '48',
    'LDA': '00',
    'COMP': '28',
    'JEQ': '30',
    'JSUB': '48',
    'J': '3C',
    'STA': '0C',
    'LDL': '08',
    'RSUB': '4C',
    'LDX': '04',
    'TD': 'E0',
    'RD': 'D8',
    'STCH': '54',
    'TIX': '2C',
    'JLT': '38',
    'STX': '10',
    'LDCH': '50',
    'WD': 'DC'
}

assembly = open('text.txt', 'r')
lines = assembly.readlines()
lines = [x.strip() for x in lines if x.strip() != '']

loc_map = {}
location_counter = {}
loc = lines[0].strip().split()[2]
loc_map[0] = loc

# First Pass
for i in range(1, len(lines)):
    arr = lines[i].strip().split()
    loc_map[i] = hex(int(loc, 16)).split('x')[-1]

    if len(arr) == 3:
        location_counter[arr[0]] = hex(int(loc, 16)).split('x')[-1]

        if (arr[1] == 'BYTE'):
            if arr[2][0] == 'C':
                loc = int(loc, 16)
                loc += (len(arr[2]) - 3)
                loc = hex(loc).split('x')[-1]
                continue

            if arr[2][0] == 'X':
                loc = int(loc, 16)
                loc += math.ceil((len(arr[2]) - 3) / 2)
                loc = hex(loc).split('x')[-1]
                continue

        if (arr[1] == 'RESW'):
            loc = int(loc, 16)
            loc += 3 * int(arr[2])
            loc = hex(loc).split('x')[-1]
            continue

        if (arr[1] == 'RESB'):
            loc = int(loc)
            x = int(hex(int(arr[2])).split('x')[-1])
            loc += x
            loc = str(loc)
            continue

    loc = int(loc, 16)
    loc += 3
    loc = hex(loc).split('x')[-1]

# Second Pass
print('Loc\tLabels\t\tInstructions\t\tOperands\tObj Code')

arr = lines[0].strip().split()
print('{}\t{}\t\t{}\t\t\t{}'.format(loc_map[0], arr[0], arr[1], arr[2]))

for i in range(1, len(lines) - 1):
    arr = lines[i].strip().split()
    print('{}\t'.format(loc_map[i]), end='')

    if len(arr) == 3:
        print('{}\t\t{}\t\t\t{}\t\t'.format(arr[0], arr[1], arr[2]), end='')

        if arr[1] in ['RESW', 'RESB']:
            print()
            continue

        if arr[1] == 'BYTE':
            temp = re.sub(r'\'', '', arr[2])

            if temp[0] == 'C':
                temp = temp[1:]
                asciiToHex = ''
                for c in temp:
                    asciiToHex += hex(ord(c)).split('x')[-1]

                print('{}'.format(asciiToHex))
                continue

            if temp[0] == 'X':
                temp = temp[1:]
                print('{}'.format(temp))
                continue

        if arr[1] == 'WORD':
            temp = hex(int(arr[2])).split('x')[-1]
            print('{}'.format(temp.zfill(6)))
            continue

        print('{}'.format(opcode[arr[1]] + location_counter[arr[2]]))
        continue

    if len(arr) == 2:
        if bool(re.match(r'\w+,X', arr[1])):
            temp = opcode[arr[0]] + location_counter[arr[1].split(',')[0]]
            temp = bin(int(temp, 16)).split('b')[-1]
            temp = temp.zfill(24)
            temp = temp[:8] + '1' + temp[9:]
            temp = hex(int(temp, 2)).split('x')[-1]

            print('{}\t\t{}\t\t\t{}\t'.format('', arr[0], arr[1]), end='')
            print('{}'.format(temp))
            continue

        print('{}\t\t{}\t\t\t{}\t\t'.format('', arr[0], arr[1]), end='')
        print('{}'.format(opcode[arr[0]] + location_counter[arr[1]]))
        continue

    if len(arr) == 1:
        print('{}\t\t{}\t\t\t{}\t\t'.format('', arr[0], ''), end='')
        print('{}'.format(opcode[arr[0]] + '0000'))

arr = lines[-1].strip().split()
print(' \t \t\t{}\t\t\t{}'.format(arr[0], arr[1]))
