#include <cstdio>
#include <vector>
#include <cassert>
using namespace std;

const int N = 50005;
const int LG = 16;

int anc[N][LG];
int depth[N];
int in[N],out[N],cnt;
vector<int> adj[N];
int BIT[N];
int n,q;

void Update(int x,int val){
    if(x == 0) return;
    for(; x <= n ; x += x & -x)
        BIT[x] += val;    
}

int Query(int x){
    int res = 0;
    for(; x > 0 ; x -= x & -x)
        res += BIT[x];
    return res;    
}

void Build(int pos,int prv){
    anc[pos][0] = prv;
    depth[pos] = depth[prv] + 1;
    for(int lg = 1 ; (1 << lg) <= depth[pos] ; lg++){
        int par = anc[pos][lg - 1];
        int gpar = anc[par][lg - 1];
        anc[pos][lg] = gpar;
    } 
}

void DFS(int pos){
    //printf("dfs %d\n",pos);
    in[pos] = ++cnt;
    for(int i = 0 ; i < adj[pos].size() ; i++){
        int nxt = adj[pos][i];
        if(nxt == anc[pos][0]) continue;
        Build(nxt,pos);
        //printf("%d chld of %d\n",nxt,pos);
        DFS(nxt);
    }
    out[pos] = cnt;    
}

int LCA(int u,int v){
    if(depth[u] < depth[v]) swap(u,v);
    int diff = depth[u] - depth[v];
    for(int i = 0 ; diff > 0 ; i++)
        if(diff & (1 << i)){
            diff ^= (1 << i);
            u = anc[u][i];
        }
    int lg = 0;
    while((1 << lg) <= depth[u]) lg++;
    lg--;
    for(int i = lg ; i >= 0 ; i--)
        if((1 << i) <= depth[u] && anc[u][i] != anc[v][i]){
            u = anc[u][i];
            v = anc[v][i];
        }    
    assert(anc[u][0] == anc[v][0]);    
    return anc[u][0];    
}

void Process(int u,int v,int val){
    if(depth[u] > depth[v]) swap(u,v);
    if(in[u] <= in[v] && in[v] <= out[u]){
        //printf("case 1 %d %d %d\n",u,v,val);
        Update(in[v],val);
        u = anc[u][0];
        Update(in[u],-val);
    }
    else{
        int w = LCA(u,v);
        //printf("case 2 %d %d LCA %d %d\n",u,v,w,val);
        Update(in[u],val);
        Update(in[v],val);
        Update(in[w],-val);
        w = anc[w][0];
        Update(in[w],-val);
    }
}

void Init(){
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; i++){
        BIT[i] = 0;
        adj[i].clear();
    }
    for(int i = 1 ; i < n ; i++){
        int u,v;
        scanf("%d %d",&u,&v);
        u++;
        v++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cnt = 0;
    DFS(1);
}

void Solve(){
    scanf("%d",&q);
    while(q--){
        int u,v,val;
        scanf("%d %d %d",&u,&v,&val);
        Process(u + 1,v + 1,val);
    }
    for(int i = 1 ; i <= n ; i++){
        //printf("%d in %d out %d\n",i,in[i],out[i]);
        printf("%d\n",Query(out[i]) - Query(in[i] - 1));
    }    
}

int main(){
    depth[0] = -1;
    int tc;
    scanf("%d",&tc);
    for(int t = 1 ; t <= tc ; t++){
        Init();
        printf("Case #%d:\n",t);
        Solve();
    }
    return 0;
}
