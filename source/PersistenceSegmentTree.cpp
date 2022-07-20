int node_cnt,cp,n,m,cnt,root[MN+3];
struct data{
    int x,y;
}point[M];
struct pst{
    int l,r,v;
};
vector <pst> tree(MN*30);
inline bool cmp(const data a, const data b){
    return a.y<b.y;
}
void mk_tree(){
    int i;
    root[0] = 1;
    node_cnt = MN<<1;
    for(i=1;i<MN;i++){
        tree[i].l = i<<1;
        tree[i].r = i<<1|1;
    }
}
void update(int s, int e, int now, int idx){
    tree[now].v++;
    if(s!=e){
        int m = (s+e)/2;
        int L = tree[now].l, R = tree[now].r;
        if(idx<=m){
            tree[now].l = node_cnt;
            tree[node_cnt++] = tree[L];
            update(s,m,tree[now].l,idx);
        }
        else{
            tree[now].r = node_cnt;
            tree[node_cnt++] = tree[R];
            update(m+1,e,tree[now].r, idx);
        }
    }
}
int fnd(int s, int e, int l, int r, int p_node, int n_node){
    if(l<=s&&e<=r) return tree[n_node].v-tree[p_node].v;
    if(r<s||l>e) return 0;
    int m = s+e>>1;
    int P = p_node, N = n_node;
    return fnd(s,m,l,r,tree[P].l, tree[N].l)+fnd(m+1,e,l,r,tree[P].r, tree[N].r);
}
void Reset(){
    int i;
    for(i=1;i<=n;i++)
        point[i].x = point[i].y = 0;
    for(i=1;i<=MN;i++)
        root[i] = tree[i].l = tree[i].r = tree[i].v = 0;
}