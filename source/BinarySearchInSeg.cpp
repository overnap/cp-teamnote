int query(int x) {
	int acc, i;
	for (acc=0, i=1; i<n;) {
		if (acc + tree[i*2] < x) {
			acc += tree[i*2];
			i = i*2+1;
		} else
			i = i*2;
	}
	return i - n;
}