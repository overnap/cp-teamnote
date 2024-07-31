for (int next : e[x]) {
  if (match[next] != -1 && level[match[next]] == -1) {
    level[match[next]] = level[x] + 1;
    q.push(match[next]);
  }
} // bfs loop FIXME: 헷갈리니까 풀버전
if (level.empty() || *max_element(level.begin(), level.end()) == -1)
  break;
for (int next : e[x]) {
  if (match[next] == -1 ||
      (level[match[next]] == level[x] + 1 && dfs(match[next]))) {
    match[next] = x;
    match[x] = next;
    return true;
  }
} // dfs loop
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
  }
}
for (int i : r) {
  if (!alt.contains(i)) {
    auto &[y, x] = pos[i];
    s[y][x] = 'C';
  }
}