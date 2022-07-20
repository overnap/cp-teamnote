struct lazySeg {
	vector<ll> tree, lazy;
	void push(int n, int s, int e) {
        tree[n] += lazy[n] * (e - s + 1);
        if (s != e) {
            lazy[n*2] += lazy[n];
            lazy[n*2+1] += lazy[n];
        }
        lazy[n] = 0;
	}
	void update(int n, int s, int e, int l, int r, int v) {
		push(n, s, e);
		if (e < l || r < s)
			return;
		if (l <= s && e <= r) {
			lazy[n] += v;
			push(n, s, e);
		} else {
			int m = (s + e) / 2;
			update(n*2, s, m, l, r, v);
			update(n*2+1, m+1, e, l, r, v);
			tree[n] = tree[n*2] + tree[n*2+1];
		}
	}
	ll query(int n, int s, int e, int l, int r) {
		push(n, s, e);
		if (e < l || r < s)
			return 0;
		if (l <= s && e <= r)
			return tree[n];
        int m = (s + e) / 2;
        return query(n*2, s, m, l, r) + query(n*2+1, m+1, e, l, r);
	}
};