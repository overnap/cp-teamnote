/*
* 0 ~ (i-1)번 노드: 출발 노드, i ~ (j-1)번 노드: 도착 노드
* visited: {false,}, from: {-1,}로 초기화
* curNode = 0부터 (i-1)까지 dfs를 돌려 전부 true면 이분매칭 가능, 아니면 불가능
*/
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