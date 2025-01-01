#include <iostream>

using namespace std;

bool check (int a) {
    return a & (a << 1) & (~a << 2) & (~a << 3);
}

int main() {
    int n;
    cin >> n;
    int count;
    cin >> count;
    while (count--) {
        int index, val;
        cin >> index >> val;
        if (val == 1) {
            n = n | (1 << index);
        } else {
            n = n & (~(1 << index));
        }
        cout << (check(n) ? "YES" : "NO") << '\n';
    }
}
