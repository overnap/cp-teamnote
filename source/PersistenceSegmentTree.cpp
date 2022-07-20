struct pst {
	struct node {
		int count;
		array<int, 2> go;
		node() {
			count = 0;
			fill(go.begin(), go.end(), -1);
		}
	};
	vector<node> nodes;
	vector<int> roots;
	void init() {
		nodes.emplace_back();
		roots.push_back(0);
		function<void (int, int)> dfs = [&] (int x, int depth) {
			if (depth == 20)
				return;
			nodes[x].go[0] = nodes.size();
			nodes.emplace_back();
			dfs(nodes[x].go[0], depth+1);
			nodes[x].go[1] = nodes.size();
			nodes.emplace_back();
			dfs(nodes[x].go[1], depth+1);
		};
		dfs(0, 0);
	}
	void insert(int x) {
		roots.push_back(nodes.size());
		nodes.emplace_back();
		int curr = roots.back(), prev = roots[roots.size()-2];
		for (int i=0; i<20; ++i) {
			const int next = (x >> 19 - i) & 1;
			nodes[curr].count = nodes[prev].count + 1;
			nodes[curr].go[next] = nodes.size();
			nodes.emplace_back();
			nodes[curr].go[!next] = nodes[prev].go[!next];
			curr = nodes[curr].go[next];
			prev = nodes[prev].go[next];
		}
		nodes[curr].count = nodes[prev].count + 1;
	}
	void remove(int k) {
		nodes.resize(roots[roots.size()-k]);
		roots.resize(roots.size()-k);
	}
	int sum(int q, int x) {
		int curr = roots[q], ret = 0;
		for (int i=0; i<20; ++i) {
			const int next = (x >> 19 - i) & 1;
			if (next)
				ret += nodes[nodes[curr].go[!next]].count;
			curr = nodes[curr].go[next];
			if (nodes[curr].count == 0)
				break;
		}
		ret += nodes[curr].count;
		return ret;
	}
};