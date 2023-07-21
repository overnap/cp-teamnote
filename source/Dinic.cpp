while (true) {
	vector<int> level(n * 2 + 2, -1);
	queue<int> q;
	level[st] = 0;
	q.push(st);
	while (!q.empty()) {
		const int x = q.front();
		q.pop();
		for (int next : e[x]) {
			if (level[next] == -1 && cap[x][next] - flow[x][next] > 0) {
				level[next] = level[x] + 1;
				q.push(next);
			}
		}
	}
	if (level[dt] == -1)
		break;
	vector<int> vis(n * 2 + 1);
	function<int(int, int)> dfs = [&](int x, int total) {
		if (x == dt)
			return total;
		for (int &i = vis[x]; i < e[x].size(); ++i) {
			const int next = e[x][i];
			if (level[next] == level[x] + 1 && cap[x][next] - flow[x][next] > 0) {
				const int res = dfs(next, min(total, cap[x][next] - flow[x][next]));
				if (res > 0) {
					flow[x][next] += res;
					flow[next][x] -= res;
					return res;
				}
			}
		}
		return 0;
	};
	while (true) {
		const int res = dfs(st, 1e9 + 7);
		if (res == 0)
			break;
		ans += res;
	}
}