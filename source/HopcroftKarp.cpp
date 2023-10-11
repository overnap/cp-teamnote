vector<vector<ll>> e(sz);
vector<int> l, r;
for (int i = 0; i < n; ++i) {
  for (int j = 0; j < m; ++j) {
    if (s[i][j] == '*')
      continue;
    const int x = idx[{i, j}];
    ((i + j) % 2 ? l : r).push_back(x);
    for (int k = 0; k < 2; ++k) {
      const int ni = "12"[k] - '1' + i;
      const int nj = "21"[k] - '1' + j;
      if (ni >= n || nj >= m || s[ni][nj] == '*')
        continue;
      const int next = idx[{ni, nj}];
      e[x].push_back(next);
      e[next].push_back(x);
    }
  }
}
int flow = 0;
vector<int> match(sz, -1);
while (true) {
  vector<int> level(sz, -1);
  queue<int> q;
  for (int x : l) {
    if (match[x] == -1) {
      level[x] = 0;
      q.push(x);
    }
  }
  while (!q.empty()) {
    const int x = q.front();
    q.pop();

    for (int next : e[x]) {
      if (match[next] != -1 && level[match[next]] == -1) {
        level[match[next]] = level[x] + 1;
        q.push(match[next]);
      }
    }
  }
  if (level.empty() || *max_element(level.begin(), level.end()) == -1)
    break;
  function<bool(int)> dfs = [&](int x) {
    for (int next : e[x]) {
      if (match[next] == -1 ||
          (level[match[next]] == level[x] + 1 && dfs(match[next]))) {
        match[next] = x;
        match[x] = next;
        return true;
      }
    }
    return false;
  };
  int total = 0;
  for (int x : l) {
    if (level[x] == 0)
      total += dfs(x);
  }
  if (total == 0)
    break;
  flow += total;
}
set<int> alt;
function<void(int, bool)> dfs = [&](int x, bool left) {
  if (alt.contains(x))
    return;
  alt.insert(x);
  for (int next : e[x]) {
    if ((next != match[x]) && left)
      dfs(next, false);
    if ((next == match[x]) && !left)
      dfs(next, true);
  }
};
for (int x : l) {
  if (match[x] == -1)
    dfs(x, true);
}
int test = 0;
for (int i : l) {
  if (alt.contains(i)) {
    auto &[y, x] = pos[i];
    s[y][x] = 'C';
    test++;
  }
}
for (int i : r) {
  if (!alt.contains(i)) {
    auto &[y, x] = pos[i];
    s[y][x] = 'C';
    test++;
  }
}