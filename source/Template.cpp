// template
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t; cin >> t;
	while (t--)
		solve();
	return 0;
}

// precision
cout.precision(16);
cout << fixed;

// gcc bit operator
__builtin_popcount(bits) // popcountll for ll
__builtin_clz(bits) // left
__builtin_ctz(bits) // right

// random number generator
random_device rd;
mt19937 mt;
uniform_int_distribution<> half(0, 1);
cout << half(mt);

// 128MB = int * 33,554,432