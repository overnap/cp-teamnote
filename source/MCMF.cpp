void mcmf(){
	int cp = 0;
	while(cp<2){
		int prev[MN],dist[MN],inq[MN]={0};
		queue <int> Q;
		fill(prev, prev+MN, -1);
		fill(dist, dist+MN, INF);
		dist[S] = 0; inq[S] = 1;
		Q.push(S);
		while(!Q.empty()){
			int cur= Q.front();
			Q.pop();
			inq[cur] = 0;
			for(int nxt: adj[cur]){
				if(cap[cur][nxt] - flow[cur][nxt] > 0 &&
						dist[nxt] > dist[cur]+cst[cur][nxt]){
					dist[nxt] = dist[cur] + cst[cur][nxt];
					prev[nxt] = cur;
					if(!inq[nxt]){
						Q.push(nxt);
						inq[nxt] = 1;
					}
				}
			}
		}
		if(prev[E]==-1) break;
		int tmp = INF;
		for(int i=E;i!=S;i=prev[i])
			tmp = min(tmp, cap[prev[i]][i]-flow[prev[i]][i]);
		for(int i=E;i!=S;i=prev[i]){
			ans += tmp * cst[prev[i]][i];
			flow[prev[i]][i] += tmp;
			flow[i][prev[i]] -= tmp;
		}
		cp++;
	}
}