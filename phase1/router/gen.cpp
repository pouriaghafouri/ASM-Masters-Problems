#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "bad usage\n";
        return 2;
    }

    long long seed = stoll(argv[1]);
    long long prob = stoll(argv[2]);
    srand(seed);
    for (int i = 0; i < 2; ++i) {
        int num = 0;
        for (int j = 0; j < 32; ++j) {
            num = num << 1;
            if (rand() % 100 < prob) num |= 1;
        }
        cout << endl;
        cout << num << endl;
    }
    return 0;
}
