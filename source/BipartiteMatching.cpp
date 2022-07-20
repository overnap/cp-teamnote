vector<int> from(n, -1);
vector<bool> visited(n, false);
bool dfs(vector<vector<int>>& adjList, vector<bool>& visited, vector<int>& from, int curNode) {
    for (int nextNode : adjList[curNode]) {
        if (from[nextNode] == -1) {
            from[nextNode] = curNode;
            return true;
        }
    }
    for (int nextNode : adjList[curNode]) {
        if (visited[nextNode]) continue;
        visited[nextNode] = true;
        if (dfs(adjList, visited, from, from[nextNode])) {
            from[nextNode] = curNode;
            return true;
        }
    }
    return false;
}