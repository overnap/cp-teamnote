static constexpr ll INF = 2e18;
struct lin {
	ll a, b;
	ll f(ll x) { return a*x + b; }
};
struct lichao {
	struct node {
		int l, r;
		lin line;
	};
	vector<node> tree;
	void init() { tree.push_back({-1, -1, { 0, -INF }}); }
	void update(ll s, ll e, int n, const lin &line) {
		lin hi = tree[n].line;
		lin lo = line;
		if (hi.f(s) < lo.f(s))
			swap(lo, hi);
		if (hi.f(e) >= lo.f(e)) {
			tree[n].line = hi;
			return;
		}
		const ll m = s + e >> 1;
		if (hi.f(m) > lo.f(m)) {
			tree[n].line = hi;
			if (tree[n].r == -1) {
				tree[n].r = tree.size();
				tree.push_back({-1, -1, { 0, -INF }});
			}
			update(m+1, e, tree[n].r, lo);
		} else {
			tree[n].line = lo;
			if (tree[n].l == -1) {
				tree[n].l = tree.size();
				tree.push_back({-1, -1, { 0, -INF }});
			}
			update(s, m, tree[n].l, hi);
		}
	}
	ll query(ll s, ll e, int n, ll x) {
		if (n == -1)
			return -INF;
		const ll m = s + e >> 1;
		if (x <= m)
			return max(tree[n].line.f(x), query(s, m, tree[n].l, x));
		else
			return max(tree[n].line.f(x), query(m+1, e, tree[n].r, x));
	}
};