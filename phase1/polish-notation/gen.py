from operator import ge
import random

random.seed(42)

testnum = 0
msk = (1<<64)-1

def genExpr(n):
    if n == 0:
        k = random.randint(0, 9)
        return str(k), k
    m = random.randint(0, n - 1)
    p = random.uniform(0, 1)
    if p < 0.4:
        op = '+'
        a, ka = genExpr(m)
        b, kb = genExpr(n - m - 1)
        return f'{op}{a}{b}', (ka + kb) & msk
    if p < 0.7:
        op = '-'
        a, ka = genExpr(m)
        b, kb = genExpr(n - m - 1)
        return f'{op}{a}{b}', (ka - kb) & msk
    if True:
        op = '*'
        a, ka = genExpr(m)
        b, kb = genExpr(n - m - 1)
        return f'{op}{a}{b}', (ka * kb) & msk

def genTest(n):
    global testnum
    testnum += 1
    expr, k = genExpr(n)
    with open(f'tests/input{testnum}.in', 'w') as f:
        f.write(f'{expr}\n')
    with open(f'tests/input{testnum}.out', 'w') as f:
        f.write(f'{k}\n')

genTest(2)
genTest(3)
genTest(5)
genTest(30)
genTest(1000)
genTest(10000)
genTest(49999)
genTest(49999)
genTest(49999)
genTest(49999)
genTest(49999)
genTest(49999)
