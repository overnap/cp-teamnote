struct seg {
  int n;
  vector<int> tree;
  void update(int x, int v) {
    tree[x += n] = v;
    for (x /= 2; x > 0; x /= 2) tree[x] = max(tree[x * 2], tree[x * 2 + 1]);
  }
  int query(int l, int r) {
    int ret = 0;
    for (l += n, r += n; l <= r; l /= 2, r /= 2) {
      if (l % 2) ret = max(ret, tree[l++]);
      if (r % 2 == 0) ret = max(ret, tree[r--]);
    }
    return ret;
  }
};