struct pst {
  struct node {
    int cnt = 0;
    array<int, 2> go{};
  };
  vector<node> tree;
  vector<int> roots;
  pst() {
    roots.push_back(1);
    tree.resize(1 << 18);
    for (int i = 1; i < (1 << 17); ++i) {
      tree[i].go[0] = i * 2;
      tree[i].go[1] = i * 2 + 1;
    }
  }
  int insert(int x, int prev) {
    int curr = tree.size();
    roots.push_back(curr);
    tree.emplace_back();
    for (int i = 16; i >= 0; --i) {
      const int next = (x >> i) & 1;
      tree[curr].go[next] = tree.size();
      tree.emplace_back();
      tree[curr].go[!next] = tree[prev].go[!next];
      tree[curr].cnt = tree[prev].cnt + 1;
      curr = tree[curr].go[next];
      prev = tree[prev].go[next];
    }
    tree[curr].cnt = tree[prev].cnt + 1;
    return roots.back();
  }
  int query(int u, int v, int lca, int lca_par, int k) {
    int ret = 0;
    for (int i = 16; i >= 0; --i) {
      const int cnt = tree[tree[u].go[0]].cnt + tree[tree[v].go[0]].cnt -
                      tree[tree[lca].go[0]].cnt - tree[tree[lca_par].go[0]].cnt;
      if (cnt >= k) {
        u = tree[u].go[0];
        v = tree[v].go[0];
        lca = tree[lca].go[0];
        lca_par = tree[lca_par].go[0];
      } else {
        k -= cnt;
        u = tree[u].go[1];
        v = tree[v].go[1];
        lca = tree[lca].go[1];
        lca_par = tree[lca_par].go[1];
        ret += 1 << i;
      }
    }
    return ret;
  }
};