import advent as adv

def test_smoke():
    assert adv.func(3) == 5


# -------------- DAY 1---------------------
def test_fuel_12():
    assert adv.calculateFuel(12) == 2

def test_fuel_2():
    assert adv.calculateFuel(2) == 0

def test_fuel_14():
    assert adv.calculateFuel(14) == 2

def test_day_1():
    assert adv.day_1() == 3266288

def test_fuel_rec_14():
    assert adv.calculateFuelRecursive(14) == 2

def test_fuel_rec_1969():
    assert adv.calculateFuelRecursive(1969) == 966

def test_fuel_rec_100756():
    assert adv.calculateFuelRecursive(100756) == 50346

def test_day_1_p2():
    assert adv.day_1_p2() == 4896582