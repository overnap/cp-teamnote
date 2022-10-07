while (true) {
    vector<int> prev(n, -1);
    queue<int> q;
    q.push(0);
    while (!q.empty() && prev[n-1] == -1) {
        const int x = q.front();
        q.pop();

        for (int next : e[x]) {
            if (cap[x][next] - flow[x][next] > 0 && prev[next] == -1) {
                prev[next] = x;
                q.push(next);
            }
        }
    }
    if (prev[n-1] == -1)
        break;
    int bot = 1e9+7;
    for (int i=n-1; i!=0; i=prev[i])
        bot = min(bot, cap[prev[i]][i] - flow[prev[i]][i]);
    for (int i=n-1; i!=0; i=prev[i]) {
        flow[prev[i]][i] += bot;
        flow[i][prev[i]] -= bot;
    }
}