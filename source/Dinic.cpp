int din_bfs(){ //level graph
	fill(level,level+MN,-1);
	level[S] = 0;
	queue<int> Q;
	Q.push(S);
	while(!Q.empty()){
		int cur = Q.front();
		Q.pop();
		for(int nxt: adj[cur]){
			if(level[nxt]==-1&&cap[cur][nxt]-flow[cur][nxt]>0){
				level[nxt] = level[cur]+1;
				Q.push(nxt);
			}
		}
	}
	return level[E] != -1;
}
int din_dfs(int cur, int des, int fl){ //flow
	if(cur==des) return fl;
	for(int &i=work[cur];i<adj[cur].size();i++){
		int nxt = adj[cur][i];
		if(level[nxt]==level[cur]+1&&cap[cur][nxt]-flow[cur][nxt]>0){
			int df = din_dfs(nxt, des, min(cap[cur][nxt]-flow[cur][nxt],fl));
			if(df>0){
				flow[cur][nxt] += df;
				flow[nxt][cur] -= df;
				return df;
			}
		}
	}	
	return 0;
}
void dinic(){
	int tot=0;
	while(din_bfs()){
		fill(work, work+MN, 0);
		while(1){
			int fl = din_dfs(S,E,INF);
			if(!fl) break;
			tot += fl;
		}
	}
	ans = tot;
}