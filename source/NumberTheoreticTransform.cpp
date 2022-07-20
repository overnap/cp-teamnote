// w is the root of mod e.g. 3/998244353 and 5/1012924417
void ntt(vector<ll> &f, const ll w, const ll mod) {
	const int n = f.size();
	if (n == 1)
		return;
	vector<ll> odd(n/2), even(n/2);
	for (int i=0; i<n; ++i)
		(i&1 ? odd : even)[i/2] = f[i];
	ntt(odd, w*w%mod, mod);
	ntt(even, w*w%mod, mod);
	ll x = 1;
	for (int i=0; i<n/2; ++i) {
		f[i] = (even[i] + x * odd[i] % mod) % mod;
		f[i+n/2] = (even[i] - x * odd[i] % mod + mod) % mod;
		x = x*w%mod;
	}
}