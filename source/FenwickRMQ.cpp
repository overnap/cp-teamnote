struct fenwick {
  static constexpr pii INF = {1e9 + 7, -(1e9 + 7)};
  vector<pii> tree1, tree2;
  const vector<int> &arr;
  static pii op(pii l, pii r) {
    return {min(l.first, r.first), max(l.second, r.second)};
  }
  fenwick(const vector<int> &a) : arr(a) {
    const int n = a.size();
    tree1.resize(n + 1, INF);
    tree2.resize(n + 1, INF);
    for (int i = 0; i < n; ++i)
      update(i, a[i]);
  }
  void update(int x, int v) {
    for (int i = x + 1; i < tree1.size(); i += i & -i)
      tree1[i] = op(tree1[i], {v, v});
    for (int i = x + 1; i > 0; i -= i & -i)
      tree2[i] = op(tree2[i], {v, v});
  }
  pii query(int l, int r) {
    pii ret = INF;
    l++, r++;
    int i;
    for (i = r; i - (i & -i) >= l; i -= i & -i)
      ret = op(tree1[i], ret);
    for (i = l; i + (i & -i) <= r; i += i & -i)
      ret = op(tree2[i], ret);
    ret = op({arr[i - 1], arr[i - 1]}, ret);
    return ret;
  }
};