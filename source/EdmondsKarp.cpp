int getMaxFlow(vector<vector<int>>& adjList, int source, int sink) {
    int nodeCnt = adjList.size();
    vector<vector<int>> flow(nodeCnt, vector<int>(nodeCnt));
    int ret = 0;
    vector<vector<int>> adj(nodeCnt);
    for (int i = 0; i < nodeCnt; i++) {
        for (int j = 0; j < nodeCnt; j++) {
            if (adjList[i][j] != 0) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    while (true) { // bfs
        vector<int> parents(nodeCnt, -1);
        parents[source] = source;
        queue<int> q;
        q.push(source);
        while (!q.empty() && parents[sink] == -1) {
            int curNode = q.front();
            q.pop();
            for (int nextNode : adj[curNode]) {
                if (adjList[curNode][nextNode] - flow[curNode][nextNode] > 0 && parents[nextNode] == -1) {
                    parents[nextNode] = curNode;
                    q.push(nextNode);
                }
            }
        }
        if (parents[sink] == -1) break;
        int amount = INF;
        for (int curNode = sink; curNode != source; curNode = parents[curNode])
            amount = min(adjList[parents[curNode]][curNode] - flow[parents[curNode]][curNode], amount);
        for (int curNode = sink; curNode != source; curNode = parents[curNode]) {
            flow[parents[curNode]][curNode] += amount;
            flow[curNode][parents[curNode]] -= amount;
        }
        ret += amount;
    }
    return ret;
}