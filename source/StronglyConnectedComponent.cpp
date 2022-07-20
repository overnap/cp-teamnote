int idx = 0, scnt = 0;
vector<int> scc(n, -1), vis(n, -1), st;
function<int (int)> dfs = [&] (int x) {
	int ret = vis[x] = idx++;
	st.push_back(x);
	for (int next : e[x]) {
		if (vis[next] == -1)
			ret = min(ret, dfs(next));
		else if (scc[next] == -1)
			ret = min(ret, vis[next]);
	}
	if (ret == vis[x]) {
		while (!st.empty()) {
			const int t = st.back();
			st.pop_back();
			scc[t] = scnt;
			if (t == x)
				break;
		}
		scnt++;
	}
	return ret;
};