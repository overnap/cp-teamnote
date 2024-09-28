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
vector<int> mult(vector<int> f, vector<int> g) {
  int sz;
  for (sz = 1; sz < f.size() + g.size(); sz *= 2);
  vector<int> ret(sz);
  f.resize(sz), g.resize(sz);
  int w = modpow(W, (MOD - 1) / sz, MOD);
  ntt(f, w), ntt(g, w);
  for (int i = 0; i < sz; ++i)
    ret[i] = 1LL * f[i] * g[i] % MOD;
  ntt(ret, modpow(w, MOD - 2, MOD));
  const int szinv = modpow(sz, MOD - 2, MOD);
  for (int i = 0; i < sz; ++i)
    ret[i] = 1LL * ret[i] * szinv % MOD;
  while (!ret.empty() && ret.back() == 0)
    ret.pop_back();
  return ret;
}
vector<int> inv(vector<int> f, const int DMOD) {
  vector<int> ret = {modpow(f[0], MOD - 2, MOD)};
  for (int i = 1; i < DMOD; i *= 2) {
    vector<int> tmp(f.begin(), f.begin() + min((int)f.size(), i * 2));
    tmp = mult(ret, tmp);
    tmp.resize(i * 2);
    for (int &x : tmp) x = (MOD - x) % MOD;
    tmp[0] = (tmp[0] + 2) % MOD;
    ret = mult(ret, tmp);
    ret.resize(i * 2);
  }
  ret.resize(DMOD);
  return ret;
}
vector<int> div(vector<int> a, vector<int> b) {
  if (a.size() < b.size()) return {};
  const int DMOD = a.size() - b.size() + 1;
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  if (a.size() > DMOD) a.resize(DMOD);
  if (b.size() > DMOD) b.resize(DMOD);
  b = inv(b, DMOD);
  auto res = mult(a, b);
  res.resize(DMOD);
  reverse(res.begin(), res.end());
  while (!res.empty() && res.back() == 0) res.pop_back();
  return res;
}
vector<int> mod(vector<int> &&a, vector<int> b) {
  auto tmp = mult(div(a, b), b);
  tmp.resize(a.size());
  for (int i = 0; i < a.size(); ++i)
		a[i] = (a[i] - tmp[i] + MOD) % MOD;
  while (!a.empty() && a.back() == 0) a.pop_back();
  return a;
}
vector<int> res = {1}, xn = {0, 1};
while (n) {
  if (n & 1) res = mod(mult(res, xn), c);
  n /= 2;
  xn = mod(mult(xn, xn), c);
}