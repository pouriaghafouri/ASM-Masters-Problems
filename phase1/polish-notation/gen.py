from operator import ge
import random

random.seed(42)

testnum = 0

def genExpr(n, maxk):
    if maxk == 0:
        return str(0), 0
    if n == 0:
        k = random.randint(1, maxk)
        return str(k), k
    m = random.randint(0, n - 1)
    p = random.uniform(0, 1)
    if p < 0.4:
        op = '+'
        a, ka = genExpr(m, maxk)
        b, kb = genExpr(n - m - 1, maxk - ka)
        return f'{op} {a} {b}', ka + kb
    if p < 0.7:
        op = '-'
        a, ka = genExpr(m, maxk)
        b, kb = genExpr(n - m - 1, ka)
        return f'{op} {a} {b}', ka - kb
    if p < 0.9:
        op = '*'
        a, ka = genExpr(m, maxk)
        b, kb = genExpr(n - m - 1, maxk // ka if ka > 0 else maxk)
        return f'{op} {a} {b}', ka * kb
    op = '/'
    a, ka = genExpr(m, maxk)
    b, kb = genExpr(n - m - 1, min(ka + 1, maxk))
    if kb == 0:
        kb = 1
        b = '1'
    return f'{op} {a} {b}', ka // kb

def genTest(n, maxk):
    global testnum
    testnum += 1
    expr, k = genExpr(n, maxk)
    with open(f'tests/input{testnum}.in', 'w') as f:
        f.write(f'{expr}\n')

genTest(2, 10)
genTest(3, 10)
genTest(5, 100)
genTest(30, 1000)
genTest(1000, 100000)
genTest(10000, 100000000)
genTest(100000, 1000000000)
genTest(100000, 1000000000)
genTest(100000, 1000000000)
genTest(100000, 1000000000)
genTest(100000, 1000000000)
genTest(100000, 1000000000)
