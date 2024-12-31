#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
int main() {
    std::vector<void **> memry;
    for (int i = 0; i < 4096; i++) {
        memry.push_back((void **)malloc(4096 * sizeof(void *)));
        for (int j = 0; j < 4096 / sizeof(int); j++)
            ((int *)memry[i])[j] = rand();
    }

    srand(time(0));
    auto flagidx = rand() % 4096;
    auto flagptr = memry[flagidx];
    *(long long *)flagptr = 0xdeadbeef;
    auto x = rand() % 64;
    auto y = rand() % 64;
    auto i = rand() % 4096;
    if (i == flagidx)
        i = (i + 1) % 4096;
    auto p1 = 63;
    auto p2 = 63 * 64;
    auto p3 = 4095 * 64 * 64;
    std::cout << "h1 : " << (x | y * 64 | i * 64 * 64) << std::endl;
    std::cout << "h2 : " << memry.data() << std::endl;

    auto dsp = (memry.data() + i);
    auto ds = *dsp;
    auto flptr = *dsp + (x + y * 64);
    *flptr = flagptr;
    // (memry + i * 8) DS-ptr
    //

    *((void **)memry[i] + x + y * 64) = flagptr;

    while (1) {
        unsigned long x1;
        scanf("%lx", &x1);
        printf("0x%lx\n", *(unsigned long *)x1);
        if (x1 == (unsigned long)flagptr)
            printf("yay! our flag is the last line including 0x\n");
    }
}
