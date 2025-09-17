void off(int x, int s, int e, int l, int r, int v) {
	push(x, s, e);
	if (e < l || r < s || (tree[x].o & v) == 0)
		return;
	if (l <= s && e <= r && !(v & (tree[x].a^tree[x].o))) {
		tree[x].l -= v & tree[x].o;
		push(x, s, e);
	} else {
		const int m = (s+e) / 2;
		off(x*2, s, m, l, r, v);
		off(x*2+1, m+1, e, l, r, v);
		tree[x] = tree[x*2] + tree[x*2+1];
	}
}
void on(int x, int s, int e, int l, int r, int v) {
	push(x, s, e);
	if (e < l || r < s || (tree[x].a & v) == v)
		return;
	if (l <= s && e <= r && !(v & (tree[x].a^tree[x].o))) {
		tree[x].l += v & ~tree[x].o;
		push(x, s, e);
	} else {
		const int m = (s+e) / 2;
		on(x*2, s, m, l, r, v);
		on(x*2+1, m+1, e, l, r, v);
		tree[x] = tree[x*2] + tree[x*2+1];
	}
}
int sum(int x, int s, int e, int l, int r) {
	push(x, s, e);
	if (e < l || r < s)
		return 0;
	if (l <= s && e <= r)
		return tree[x].x;
	const int m = (s+e) / 2;
	return max(sum(x*2, s, m, l, r), sum(x*2+1, m+1, e, l, r));
}