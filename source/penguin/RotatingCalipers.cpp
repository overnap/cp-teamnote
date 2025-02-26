array<pii, 2> farthestpoints(pii* H, int n) {
    int j = n < 2 ? 0 : 1;
    pair<ll, array<pii, 2>> res({0, {H[0], H[0]}});
    for (int i = 0; i < j; i++)
        for (;; j = (j + 1) % n) {
            res = max(res, {distsq(H[i], H[j]), {H[i], H[j]}});
            if ((H[(j + 1) % n] - H[j]) / (H[i + 1] - H[i]) >= 0) break;
        }
    return res.second;
}