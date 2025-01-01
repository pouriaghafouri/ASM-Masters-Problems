#include <bits/stdc++.h>
using namespace std;

int main()
{
	int x, y;
	cin >> x >> y;
	bool a = 1, b = 1;
	for (int i = 0; i < 32; i++) {
		int a2 = (x&1) && (a || (b && (y&1)));
		int b2 = (y&1) && (b || (a && (x&1)));
		x >>= 1;
		y >>= 1;
		a = a2;
		b = b2;
	}
	cout << (a || b? "YES\n": "NO\n");
}
