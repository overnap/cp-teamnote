pair<int, int> getMCMF(vector<vector<int>>& capacity, vector<vector<int>>& costs, int source, int sink) {
    int nodeCnt = capacity.size();
    vector<vector<int>> flow(nodeCnt, vector<int>(nodeCnt));
    int minCost = 0, maxFlow = 0;

    vector<vector<int>> adj(nodeCnt);
    for (int i = 0; i < nodeCnt; i++) {
        for (int j = i; j < nodeCnt; j++) {
            if (capacity[i][j] != 0 || capacity[j][i] != 0) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    while (true) {
        // spfa
        vector<int> parents(nodeCnt, -1), dists(nodeCnt, INF);
        vector<bool> inQ(nodeCnt, false);
        parents[source] = source;
        queue<int> q;
        q.push(source);
        inQ[source] = true;
        dists[source] = 0;
        while (!q.empty()) {
            int curNode = q.front();
            q.pop();
            inQ[curNode] = false;

            for (int nextNode : adj[curNode]) {
                if (capacity[curNode][nextNode] - flow[curNode][nextNode] > 0 && dists[nextNode] > dists[curNode] + costs[curNode][nextNode]) {
                    parents[nextNode] = curNode;
                    dists[nextNode] = dists[curNode] + costs[curNode][nextNode];
                    if (!inQ[nextNode]) {
                        q.push(nextNode);
                        inQ[nextNode] = true;
                    }
                }
            }
        }

        if (parents[sink] == -1) break;

        int amount = INF + 2;
        for (int curNode = sink; curNode != source; curNode = parents[curNode])
            amount = min(capacity[parents[curNode]][curNode] - flow[parents[curNode]][curNode], amount);

        for (int curNode = sink; curNode != source; curNode = parents[curNode])
        {
            minCost += amount * costs[parents[curNode]][curNode];
            flow[parents[curNode]][curNode] += amount;
            flow[curNode][parents[curNode]] -= amount;
        }

        maxFlow += amount;
    }
    return { minCost, maxFlow };
}
