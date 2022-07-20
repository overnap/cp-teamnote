struct mst {
	int n;
	vector<vector<int>> tree;
	void init(vector<int> &arr) {
		n = 1 << (int)ceil(log2(arr.size()));
		tree.resize(n*2);
		for (int i=0; i<arr.size(); ++i)
			tree[n+i].push_back(arr[i]);
		for (int i=n-1; i>0; --i) {
			tree[i].resize(tree[i*2].size() + tree[i*2+1].size());
			merge(tree[i*2].begin(), tree[i*2].end(),
				tree[i*2+1].begin(), tree[i*2+1].end(), tree[i].begin());
		}
	}
	int sum(int l, int r, int k) {
		int ret = 0;
		for (l+=n, r+=n; l<=r; l/=2, r/=2) {
			if (l%2)
				ret += upper_bound(tree[l].begin(), tree[l].end(), k) - tree[l].begin(), l++;
			if (r%2 == 0)
				ret += upper_bound(tree[r].begin(), tree[r].end(), k) - tree[r].begin(), r--;
		}
		return ret;
	}
};