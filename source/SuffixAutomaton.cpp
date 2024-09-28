struct suffix_automaton {
  struct node {
    int len, slink;
    map<int, int> go;
  };
  int last = 0;
  vector<node> sa = {{0, -1}};
  void insert(int x) {
    sa.emplace_back(sa[last].len + 1, 0);
    int p = last;
    last = sa.size() - 1;
    while (p != -1 && !sa[p].go.contains(x))
      sa[p].go[x] = last, p = sa[p].slink;
    if (p != -1) {
      const int t = sa[p].go[x];
      if (sa[p].len + 1 < sa[t].len) {
        const int q = sa.size();
        sa.push_back(sa[t]);
        sa[q].len = sa[p].len + 1;
        sa[t].slink = q;
        while (p != -1 && sa[p].go[x] == t)
          sa[p].go[x] = q, p = sa[p].slink;
        sa[last].slink = q;
      } else
        sa[last].slink = t;
    }
  }
};