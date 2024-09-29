struct lucy_hedgehog {
  ll n, sq;
  vector<int> sieve, psum;
  vector<ll> a, b, d;
  ll f(ll x) {
    if (x <= sq) return a[x];
    else return b[n / x];
  };
  lucy_hedgehog(ll _n) {
    n = _n, sq = sqrt(n);
    sieve.resize(sq + 1, 1);
    psum.resize(sq + 1);
    sieve[0] = sieve[1] = false;
    for (ll i = 4; i <= sq; i += 2) sieve[i] = false;
    for (ll i = 3; i <= sq; i += 2) {
      if (!sieve[i]) continue;
      for (ll j = i * i; j <= sq; j += i) sieve[j] = false;
    }
    for (int i = 2; i <= sq; ++i) psum[i] = psum[i - 1] + sieve[i];
    a.resize(sq + 1), d = b = a;
    for (int i = 1; i <= sq; ++i) {
      d[i] = n / i;    // bottleneck is division
      a[i] = i - 1;    // dp[i]
      b[i] = d[i] - 1; // dp[n/i]
    }
    for (ll i = 2; i <= sq; ++i) {
      if (!sieve[i]) continue;
      for (ll j = 1; j <= sq && d[j] >= i * i; ++j)
        b[j] = b[j] - (f(d[j] / i) - psum[i - 1]);
      for (int j = sq; j >= i * i; --j)
        a[j] = a[j] - (f(j / i) - psum[i - 1]);
    }
  }
};