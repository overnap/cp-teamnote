struct dsparse {
  using T = array<ll, 501>;
  using V = pii;
  static constexpr T E = {};
  static constexpr V I = {};
  int n, level;
  vector<vector<T>> table;
  T merge(T x, V v) {
    for (int i = 500 - v.first; i >= 0; --i)
      x[i + v.first] = max(x[i + v.first], x[i] + v.second);
    return x;
  }
  void make(vector<V> a) {
    level = bit_width(a.size() - 1);
    level = max(level, 1);
    n = 1 << level;
    table.resize(level, vector<T>(a.size(), E));
    function<void(int, int, int)> go = [&](int t, int l, int r) {
      if (l >= r)
        return;
      const int m = (l + r) / 2;
      for (int i = m + 1; i <= min(r, int(a.size()) - 1); ++i)
        table[t][i] = merge(i > m + 1 ? table[t][i - 1] : E, a[i]);
      for (int i = min(m, int(a.size()) - 1); i >= l; --i)
        table[t][i] = merge(i < m ? table[t][i + 1] : E, a[i]);
      go(t - 1, l, m);
      go(t - 1, m + 1, r);
    };
    go(level - 1, 0, n - 1);
  }
  pair<T, T> query(int l, int r) {
    if (l > r) return {E, E};
    if (l == r) return {table[0][l], E};
    const int t = 31 - __builtin_clz(l ^ r);
    return {table[t][l], table[t][r]};
  }
};