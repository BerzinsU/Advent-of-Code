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

# -------------- DAY 2---------------------

def test_do_op_1():
    assert adv.do_op([1,0,0,0,99],0)[0] == 2

def test_do_op_2():
    assert adv.do_op([2,3,0,3,99],0)[3] == 6

def test_do_op_3():
    assert adv.do_op([2,4,4,5,99,0],0)[5] == 9801

def test_do_op_4():
    assert adv.do_seq([1,1,1,4,99,5,6,0,99])[0] == 30

def test_day_2():
    assert adv.day_2() == 3058646

def test_day_2_p2():
    assert adv.day_2_p2() == 8976