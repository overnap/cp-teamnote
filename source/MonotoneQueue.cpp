auto cross = [&](ll p, ll q) {
  ll lo = min(p, q) - 1, hi = n + 1;
  while (lo + 1 < hi) {
    const ll mid = (lo + hi) / 2;
    if (f(p, mid) < f(q, mid)) lo = mid;
    else hi = mid;
  }
  return hi;
};
deque<pll> st;
for (int i = 1; i <= n; ++i) {
  pll curr{i - 1, 0};
  while (!st.empty() &&
          (curr.second = cross(st.back().first, i - 1)) <= st.back().second)
    st.pop_back();
  st.push_back(curr);
  while (st.size() > 1 && st[1].second <= i) st.pop_front();
  dp[i] = f(st[0].first, i);
}