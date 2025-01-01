#include <iostream>

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    a = ~a;
    b = ~b;
    bool bad1 = a & b;
    bool bad2 = a & (b << 1);
    bool bad3 = (a << 1) & b;
    bool ans = !(bad1 || bad2 || bad3);
    cout << (ans ? "YES\n" : "NO\n");
}
