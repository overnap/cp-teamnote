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
  for (int x : l) if (level[x] == 0)  total += dfs(x);
  if (total == 0) break;
  flow += total;
}
set<int> alt; // Konig
function<void(int, bool)> dfs = [&](int x, bool left) {
  if (alt.contains(x)) return;
  alt.insert(x);
  for (int next : e[x]) {
    if ((next != match[x]) && left) dfs(next, false);
    if ((next == match[x]) && !left) dfs(next, true);
  }
};
for (int x : l) if (match[x] == -1) dfs(x, true);
int test = 0;
for (int i : l) {
  if (alt.contains(i)) {
    auto &[y, x] = pos[i];
    s[y][x] = 'C';
  }
}
for (int i : r) {
  if (!alt.contains(i)) {
    auto &[y, x] = pos[i];
    s[y][x] = 'C';
  }
}