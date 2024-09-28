while (true) {
  vector<int> level(dt, -1);
  queue<int> q;
  level[st] = 0;
  q.push(st);
  while (!q.empty()) {
    const int x = q.front();
    q.pop();
    for (int nid : eid[x]) {
      const auto &[_, next, cap, flow] = e[nid];
      if (level[next] == -1 && cap - flow > 0) {
        level[next] = level[x] + 1;
        q.push(next);
      }
    }
  }
  if (level[dt] == -1) break;
  vector<int> vis(dt);
  function<int(int, int)> dfs = [&](int x, int total) {
    if (x == dt) return total;
    for (int &i = vis[x]; i < eid[x].size(); ++i) {
      auto &[_, next, cap, flow] = e[eid[x][i]];
      if (level[next] == level[x] + 1 && cap - flow > 0) {
        const int res = dfs(next, min(total, cap - flow));
        if (res > 0) {
          auto &[_next, _x, bcap, bflow] = e[eid[x][i] ^ 1];
          assert(next == _next && x == _x);
          flow += res;
          bflow -= res;
          return res;
        }
      }
    }
    return 0;
  };
  while (true) {
    const int res = dfs(st, 1e9 + 7);
    if (res == 0) break;
    ans += res;
  }
}