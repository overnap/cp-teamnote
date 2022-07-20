vector<int> lo(q, -1), hi(q, m), answer(q);
while (true) {
    int fin = 0;
    vector<vector<int>> mids(m);
    for (int i=0; i<q; ++i) {
        if (lo[i] + 1 < hi[i])
            mids[(lo[i] + hi[i])/2].push_back(i);
        else
            fin++;
    }
    if (fin == q)
        break;
    ufind uf;
    uf.init(n+1);
    for (int i=0; i<m; ++i) {
        const auto &[eig, a, b] = edges[i];
        uf.merge(a, b);
        for (int x : mids[i]) {
            if (uf.find(qs[x].first) == uf.find(qs[x].second)) {
                hi[x] = i;
                answer[x] = -uf.par[uf.find(qs[x].first)];
            } else
                lo[x] = i;
        }
    }
}