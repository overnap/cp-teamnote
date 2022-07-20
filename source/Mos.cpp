sort(q.begin(), q.end(), [&] (const auto &a, const auto &b) {
    if (get<0>(a)/rt != get<0>(b)/rt)
        return get<0>(a)/rt < get<0>(b)/rt;
    return get<1>(a) < get<1>(b);
});
int res = 0, s = get<0>(q[0]), e = get<1>(q[0]);
vector<int> count(1e6), result(m);
for (int i=s; i<=e; ++i)
    res += count[a[i]]++ == 0;
result[get<2>(q[0])] = res;
for (int i=1; i<m; ++i) {
    while (get<0>(q[i]) < s)
        res += count[a[--s]]++ == 0;
    while (get<1>(q[i]) > e)
        res += count[a[++e]]++ == 0;
    while (get<0>(q[i]) > s)
        res -= --count[a[s++]] == 0;
    while (get<1>(q[i]) < e)
        res -= --count[a[e--]] == 0;
    result[get<2>(q[i])] = res;
}