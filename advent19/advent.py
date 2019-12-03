import os
import functools 

def func(x):
    return x + 2

def InputPath(name):
    return os.path.join(os.path.dirname(__file__), name)


# -------------- DAY 1---------------------

def calculateFuel(weight):
    return max(0,int(int(weight)/3)-2)

def day_1():
  with open(InputPath('inputs/input_1.txt')) as f:
    weights = f.read().splitlines()
    fuels = map(calculateFuel, weights)
    return sum(fuels)

def calculateFuelRecursive(weight):
    fuel = calculateFuel(weight)
    if(fuel == 0):
        return fuel
    else:
        return fuel + calculateFuelRecursive(fuel)
        
def day_1_p2():
  with open(InputPath('inputs/input_1.txt')) as f:
    weights = f.read().splitlines()
    fuels = map(calculateFuelRecursive, weights)
    return sum(fuels)


# -------------- DAY 2---------------------

def do_op(intcode, pos):
    op = intcode[pos]
    pos_1 = intcode[pos+1]
    pos_2 = intcode[pos+2]
    result_pos = intcode[pos+3]
    if (op == 1):
        intcode[result_pos] = intcode[pos_1]+intcode[pos_2]
    else:
        intcode[result_pos] = intcode[pos_1]*intcode[pos_2]
    return intcode

def do_seq(intcode):
    seqs = intcode[::4]

    for x in range(len(seqs)):
        if (intcode[x*4] == 99):
           break
        intcode = do_op(intcode,x*4)
    return intcode

def day_2():
    with open(InputPath('inputs/input_2.txt')) as f:
        intcode = map(int, f.read().strip().split(','))
        intcode[1]=12
        intcode[2]=2
        do_seq(intcode)
        return intcode[0]

def day_2_p2():
    with open(InputPath('inputs/input_2.txt')) as f:
        intcode = map(int, f.read().strip().split(','))
        
        for x in range(99):
            for y in range(99):
                seq = list(intcode)
                seq[1]=x
                seq[2]=y
                result = do_seq(seq)[0]
                if(result == 19690720):
                    noun =x
                    verb=y
        return 100*noun+verb


# -------------- DAY 3---------------------

def traceWire(wire, board):
    return board


def day_3():
    with open(InputPath('inputs/input_3.txt')) as f:
        wires = f.read().splitlines()
        wire_1= wires[0].split(',')
        wire_2= wires[1].split(',')
        board = mb.zeros(shape[, dtype, order])
        return wire_2

print(day_3())