struct pst {
  struct node {
    dat d = ID;
    array<int, 2> go{};
  };
  int n;
  vector<node> tree;
  vector<int> roots;
  pst(int sz) {
    n = int(ceil(log2(sz)));
    roots.push_back(1);
    tree.resize(1 << (n + 1));
    for (int i = 1; i < (1 << n); ++i) {
      tree[i].go[0] = i * 2;
      tree[i].go[1] = i * 2 + 1;
    }
  }
  int insert(int x, int prev, const dat &value) {
    int curr = tree.size();
    tree.emplace_back();
    roots.push_back(curr);
    vector<int> st;
    for (int i = n - 1; i >= 0; --i) {
      st.push_back(curr);
      const int next = x >> i & 1;
      tree[curr].go[next] = tree.size();
      tree.emplace_back();
      tree[curr].go[!next] = tree[prev].go[!next];
      curr = tree[curr].go[next];
      prev = tree[prev].go[next];
    }
    tree[curr].d = value;
    while (!st.empty()) {
      const int x = st.back();
      st.pop_back();
      tree[x].d = tree[tree[x].go[0]].d + tree[tree[x].go[1]].d;
    }
    return roots.back();
  }
  dat query(int t, int l, int r) {
    function<dat(int, int, int)> q = [&](int x, int s, int e) -> dat {
      if (r < s || e < l)
        return ID;
      if (l <= s && e <= r)
        return tree[x].d;
      const int m = (s + e) / 2;
      return q(tree[x].go[0], s, m) + q(tree[x].go[1], m + 1, e);
    };
    return q(t, 0, (1 << n) - 1);
  }
  int walk(int t, int l, int k) {
    function<int(int, int, int)> q = [&](int x, int s, int e) -> int {
      if (e < l || tree[x].d.v >= k)
        return -1;
      if (s == e)
        return s;
      const int m = (s + e) / 2;
      const int res = q(tree[x].go[0], s, m);
      if (res != -1)
        return res;
      return q(tree[x].go[1], m + 1, e);
    };
    const int ret = q(t, 0, (1 << n) - 1);
    return ret == -1 ? (1 << n) - 1 : ret - 1;
  }
};