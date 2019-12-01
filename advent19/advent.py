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