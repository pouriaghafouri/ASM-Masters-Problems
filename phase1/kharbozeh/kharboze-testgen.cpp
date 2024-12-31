#include <cstdlib>
#include <fstream>
#include <ostream>
#include <string>
void make_test(int tid, int num) {
    std::ofstream input("test" + std::to_string(tid) + ".in");
    input << num << std::endl;
    std::ofstream output("test" + std::to_string(tid) + ".out");
    if (num % 2 == 0 && num > 2)
        output << "YES" << std::endl;
    else
        output << "NO" << std::endl;
}
int main(int argc, char *argv[]) {
    make_test(1, 4);
    make_test(2, 3);
    make_test(3, 2);
    make_test(4, 1);
    for (int tid = 5; tid < 10; tid++) {
        make_test(tid, rand() % 100 + 1);
    }
    for (int tid = 10; tid < 15; tid++) {
        make_test(tid, rand() % 500 + 1);
    }
    for (int tid = 15; tid < 20; tid++) {
        make_test(tid, rand() % 1000 + 1);
    }
    make_test(20, 1000);
    return 0;
}
