#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

int check_int(int x1, int x2, int y1, int y2, int r1, int r2) {

    int d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    int del = r1 - r2;
    del *= del;
    int sum = r1 + r2;
    sum *= sum;

    if (d < del)
        return 0;
    else if (d > sum)
        return 1;
    else
        return 2;
}

int colin_dx[] = {3, 4, -3, -4, 4, 0, -4, 0};
int colin_dy[] = {4, 3, 4, 3, 0, 4, 0, -4};
int colin_len[] = {5, 5, 5, 5, 4, 4, 4, 4};
void gen_colin(int tid) {
    int k = rand() % 8;
    std::ofstream input("test" + std::to_string(tid) + ".in");
    int a = 1 + rand() % 40;
    int b = 1 + rand() % 40;
    if (rand() % 2)
        b = -b;

    int x1 = rand() % 1000 - 500;
    int y1 = rand() % 1000 - 500;
    int r1 = a * colin_len[k];
    int x2 = x1 + (a - b) * colin_dx[k];
    int y2 = y1 + (a - b) * colin_dy[k];
    int r2 = std::abs(b) * colin_len[k];

    input << x1 << ' ' << y1 << ' ' << r1 << std::endl;
    input << x2 << ' ' << y2 << ' ' << r2 << std::endl;

    std::ofstream output("test" + std::to_string(tid) + ".out");
    int res = check_int(x1, x2, y1, y2, r1, r2);

    if (res == 0)
        output << "inside" << std::endl;
    else if (res == 1)
        output << "outside" << std::endl;
    else
        output << "touch" << std::endl;
}
void gen_norm(int tid, int x1, int x2, int y1, int y2, int r1, int r2) {
    std::ofstream input("test" + std::to_string(tid) + ".in");
    int a = 1 + rand() % 40;
    int b = 1 + rand() % 40;
    if (rand() % 2)
        b = -b;

    input << x1 << ' ' << y1 << ' ' << r1 << std::endl;
    input << x2 << ' ' << y2 << ' ' << r2 << std::endl;

    std::ofstream output("test" + std::to_string(tid) + ".out");
    int res = check_int(x1, x2, y1, y2, r1, r2);

    if (res == 0)
        output << "inside" << std::endl;
    else if (res == 1)
        output << "outside" << std::endl;
    else
        output << "touch" << std::endl;
}
int rand_rng() { return rand() % 2000 - 1000; }

int main() {
    gen_norm(1, 0, 0, 0, 0, 1, 2);
    gen_norm(2, 1, 1, 2, 2, 3, 3);
    gen_norm(3, 0, 4, 0, 3, 10, 5);
    gen_norm(4, 0, 12, 0, 9, 10, 5);
    for (int tid = 5; tid < 6; tid++)
        gen_norm(tid, rand_rng(), rand_rng(), rand_rng(), rand_rng(),
                 rand_rng(), rand_rng());
    for (int tid = 6; tid < 11; tid++)
        gen_colin(tid);
    for (int tid = 11; tid < 15; tid++)
        gen_norm(tid, rand_rng(), rand_rng(), rand_rng(), rand_rng(),
                 rand_rng(), rand_rng());
    for (int tid = 15; tid < 20; tid++)
        gen_colin(tid);
    for (int tid = 20; tid < 25; tid++)
        gen_norm(tid, rand_rng(), rand_rng(), rand_rng(), rand_rng(),
                 rand_rng(), rand_rng());
    for (int tid = 25; tid < 30; tid++)
        gen_colin(tid);
    for (int tid = 30; tid < 35; tid++)
        gen_norm(tid, rand_rng(), rand_rng(), rand_rng(), rand_rng(),
                 rand_rng(), rand_rng());
}
