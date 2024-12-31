import random

random.seed(42)

testnum = 0

def genTest(n):
    global testnum
    testnum += 1
    s = ''.join(random.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(n))
    if testnum == 1:
        s = "asmmasters"
    with open(f'tests/input{testnum}.in', 'w') as f:
        f.write(f'{s}\n')

genTest(5)
genTest(10)
genTest(100)
genTest(1000)
genTest(10000)
genTest(100000)
genTest(100000)
genTest(100000)
genTest(100000)
