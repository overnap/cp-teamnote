int det(vector<vector<int>> a, const int mod) {
  const int n = a.size();
  assert(a[0].size() == n);
  int ret = 1;
  for (int j = 0; j < n; ++j) {
    int p = j;
    while (p < n && a[p][j] == 0) p++;
    if (p == n) return 0;
    if (p > j) {
      ret = mod - ret;
      swap(a[j], a[p]);
    }
    ret = 1LL * ret * a[j][j] % mod;
    const int inv = modpow(a[j][j], mod - 2, mod);
    for (int k = j; k < n; ++k)
      a[j][k] = 1LL * a[j][k] * inv % mod;
    for (int i = j + 1; i < n; ++i) {
      for (int k = j; k < n; ++k)
        a[i][k] = (a[i][k] - 1LL * a[i][j] * a[j][k] % mod + mod) % mod;
    }
  }
  return ret;
}