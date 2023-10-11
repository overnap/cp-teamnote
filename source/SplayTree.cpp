struct splay_tree {
  struct node {
    node *l, *r, *p;
    ll key, sum, lazy, cnt;
    bool inv;
    node(ll value) {
      l = r = p = nullptr;
      cnt = 1;
      key = value;
      sum = value;
      lazy = 0;
      inv = false;
    }
  } *tree;
  void push(node *x) {
    x->key += x->lazy;
    if (x->inv) swap(x->l, x->r);
    if (x->l) {
      x->l->lazy += x->lazy;
      x->l->sum += x->lazy * x->l->cnt;
      x->l->inv ^= x->inv;
    }
    if (x->r) {
      x->r->lazy += x->lazy;
      x->r->sum += x->lazy * x->r->cnt;
      x->r->inv ^= x->inv;
    }
    x->lazy = 0;
    x->inv = false;
  }
  void rotate(node *x) {
    auto p = x->p;
    node *tmp;
    push(p), push(x);
    if (x == p->l) {
      p->l = tmp = x->r;
      x->r = p;
    } else {
      p->r = tmp = x->l;
      x->l = p;
    }
    x->p = p->p;
    p->p = x;
    if (tmp) tmp->p = p;
    (x->p ? (x->p->l == p ? x->p->l : x->p->r) : tree) = x;
    update(p), update(x);
  }
  void splay(node *x) {
    while (x->p) {
      auto p = x->p;
      auto g = p->p;
      if (g) rotate((x == p->l) == (p == g->l) ? p : x);
      rotate(x);
    }
  }
  void update(node *x) {
    x->cnt = 1;
    x->sum = x->key;
    if (x->l) {
      x->cnt += x->l->cnt;
      x->sum += x->l->sum;
    }
    if (x->r) {
      x->cnt += x->r->cnt;
      x->sum += x->r->sum;
    }
  }
  void init(int n) {
    node *x;
    tree = x = new node(0);
    tree->cnt = n;
    for (int i = 1; i < n; ++i) {
      x->r = new node(0);
      x->r->p = x;
      x = x->r;
      x->cnt = n - i;
    }
  }
  void add(int i, ll v) {
    find_kth(i);
    tree->sum += v;
    tree->key += v;
  }
  void add(int l, int r, ll v) {
    interval(l, r);
    auto x = tree->r->l;
    x->sum += v * x->cnt;
    x->lazy += v;
  }
  void interval(int l, int r) {
    find_kth(l - 1);
    auto x = tree;
    tree = x->r;
    tree->p = nullptr;
    find_kth(r - l + 1);
    x->r = tree;
    tree->p = x;
    tree = x;
  }
  ll sum(int l, int r) {
    interval(l, r);
    return tree->r->l->sum;
  }
  void reverse(int l, int r) {
    interval(l, r);
    tree->r->l->inv ^= true;
  }
  void insert(ll key) {
    auto x = new node(key);
    if (!tree) {
      tree = x;
      return;
    }
    auto p = tree;
    node **t;
    while (true) {
      if (key == p->key) return;
      if (key < p->key) {
        if (!p->l) {
          t = &p->l;
          break;
        }
        p = p->l;
      } else {
        if (!p->r) {
          t = &p->r;
          break;
        }
        p = p->r;
      }
    }
    *t = x;
    x->p = p;
    splay(x);
  }
  bool find(int key) {
    if (!tree) return false;
    auto p = tree;
    while (p) {
      push(p);
      if (key == p->key) break;
      if (key < p->key) {
        if (!p->l) break;
        p = p->l;
      } else {
        if (!p->r) break;
        p = p->r;
      }
    }
    splay(p);
    return key == p->key;
  }
  void erase(ll key) {
    if (!find(key)) return;
    auto p = tree;
    if (p->l) {
      if (p->r) {
        tree = p->l;
        tree->p = nullptr;
        auto x = tree;
        while (x->r)
          x = x->r;
        x->r = p->r;
        p->r->p = x;
        splay(x);
        delete p;
        return;
      }
      tree = p->l;
      tree->p = nullptr;
      delete p;
      return;
    }
    if (p->r) {
      tree = p->r;
      tree->p = nullptr;
      delete p;
      return;
    }
    delete p;
    tree = nullptr;
  }
  void find_kth(int k) {
    auto x = tree;
    while (x) {
      push(x);
      while (x->l && x->l->cnt > k) {
        x = x->l;
        push(x);
      }
      if (x->l) k -= x->l->cnt;
      if (!k--) break;
      x = x->r;
    }
    splay(x);
  }
};