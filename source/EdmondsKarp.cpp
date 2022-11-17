while (true) {
    vector<int> prev(n, -1);
    queue<int> q;
    q.push(start);
    while (!q.empty() && prev[end] == -1) {
        const int x = q.front();
        q.pop();
        for (int next : e[x]) {
            if (cap[x][next] - flow[x][next] > 0 && prev[next] == -1) {
                prev[next] = x;
                q.push(next);
            }
        }
    }
    if (prev[end] == -1)
        break;
    int bot = 1e9+7;
    for (int i=end; i!=start; i=prev[i])
        bot = min(bot, cap[prev[i]][i] - flow[prev[i]][i]);
    for (int i=end; i!=start; i=prev[i]) {
        flow[prev[i]][i] += bot;
        flow[i][prev[i]] -= bot;
    }
}