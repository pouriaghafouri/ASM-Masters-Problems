#include <bits/stdc++.h>
using namespace std;

bool ok(unsigned x)
{
	while (x) {
		if ((x & 0xf) == 0xc)
			return 1;
		x >>= 1;
	}
	return 0;
}

int main()
{
	unsigned x = ({ int y; cin >> y; y; });
	int n;
	cin >> n;
	while (n--) {
		unsigned i, b;
		cin >> i >> b;
		x &= ~(1 << i);
		x |= b << i;
		cout << (ok(x)? "YES\n": "NO\n");
	}
}
