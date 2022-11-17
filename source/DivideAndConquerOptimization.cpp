vector<vector<ll>> dp(n, vector<ll>(t));
function<void (int, int, int, int, int)> dnc = [&] (int l, int r, int s, int e, int u) {
    if (l > r)
        return;
    const int mid = (l + r) / 2;
    int opt;
    for (int i=s; i<=min(e, mid); ++i) {
        ll x = sum[i][mid] + C;
        if (i && u)
            x += dp[i-1][u-1];
        if (x >= dp[mid][u]) {
            dp[mid][u] = x;
            opt = i;
        }
    }
    dnc(l, mid-1, s, opt, u);
    dnc(mid+1, r, opt, e, u);
};
for (int i=0; i<t; ++i)
    dnc(0, n-1, 0, n-1, i);