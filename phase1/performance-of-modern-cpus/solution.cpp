#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")

int constexpr N = 100032;
unsigned short A[N];
int n;

void perform_1(int l, int r, unsigned short x)
{
	for (int i = l; i < r; i++)
		A[i] += x;
}

void perform_2(int l, int r, unsigned short x)
{
	for (int i = l; i < r; i++)
		A[i] ^= x;
}

void perform_3(int l, int r)
{
	unsigned short ans = 65535;
	for (int i = l; i < r; i++)
		ans = A[i] < ans? A[i]: ans;
	cout << ans << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> A[i];

	int q;
	cin >> q;
	while (q--) {
		int t, l, r;
		unsigned short x;
		cin >> t >> l >> r;
		if (t != 3)
			cin >> x;
		--l;
		if (t == 1)
			perform_1(l, r, x);
		if (t == 2)
			perform_2(l, r, x);
		if (t == 3)
			perform_3(l, r);
	}
}
