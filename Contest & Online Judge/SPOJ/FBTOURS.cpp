#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back

typedef pair<int,int> pii;

const int N = 100005;
const int LOG = 17;
const int MOD = (int)1e9 + 7;
vector<int> adj[N],adjbig[N];
int num[N],low[N],par[N];
int cnt;
int idbig[N];
set<pii> bridge;

int anc[N][LOG];
int depth[N];
int in[N],ot[N];
int counter;

int BIT[N];
int last[N];

int n,m;
int q,tc;
int ans;

void reset(){
    for(int i = 1 ; i <= n ; i++){
        depth[i] = 0;
        anc[i][0] = 0;
        idbig[i] = 0;
        num[i] = low[i] = par[i] = -1;
        adj[i].clear();
        adjbig[i].clear();
        last[i] = 0;
        BIT[i] = 0;
    }
    bridge.clear();
    cnt = counter = 0;
    ans = 0;
}

void update(int x,int val){
    //printf("x %d val %d\n",x,val);
    if(x == 0) return;
    for( ; x <= n ; x += x & -x) 
        BIT[x] += val;
}

int query(int x){
    int res = 0;
    while(x){
        res += BIT[x];
        x -= x & -x;
    }
    return res;
}

int kth(int x,int val){
    for(int i = 0 ; val > 0 ; i++)
        if(val & (1 << i)){
            val ^= (1 << i);
            x = anc[x][i];
        }
    return x;    
}

int lca(int u,int v){
    if(depth[u] < depth[v]) swap(u,v);
    u = kth(u,depth[u] - depth[v]);
    if(u == v) return u;
    int lg = 0;
    while((1 << lg) <= depth[u]) lg++;
    lg--;
    for(int i = lg ; i >= 0 ; i--)
        if(depth[u] >= (1 << i) && anc[u][i] != anc[v][i]){
            u = anc[u][i];
            v = anc[v][i];
        }
    return anc[u][0];    
}

void tarjan(int u){
    num[u] = low[u] = cnt++;
    for(int v : adj[u]){
        if(num[v] == -1){
            par[v] = u;
            tarjan(v);
            //printf("u %d v %d num[%d] = %d low[%d] = %d\n",u,v,u,num[u],v,low[v]);
            if(num[u] < low[v]){
                bridge.insert({u,v});
                bridge.insert({v,u});
                //printf("bridge %d %d\n",u,v);
            }
            low[u] = min(low[u],low[v]);
        }
        else if(v != par[u])
            low[u] = min(low[u],num[v]);
    }
}

void flood(int x,int val){
    idbig[x] = val;
    for(int nex : adj[x]){
        if(bridge.count({x,nex}) == 0 && idbig[nex] == 0)
            flood(nex,val);
    }
}

void build_st(int pos,int prv){
    anc[pos][0] = prv;
    depth[pos] = depth[prv] + 1;
    for(int i = 1 ; (1 << i) <= depth[pos] ; i++){
        int papa = anc[pos][i - 1];
        int grandpa = anc[papa][i - 1];
        anc[pos][i] = grandpa;
        //printf("anc[%d][%d] = %d\n",pos,i,grandpa);
    }
}

void dfs(int pos,int prv){
    in[pos] = ++counter;
    for(int nex : adjbig[pos]){
        if(nex == prv) continue;
        build_st(nex,pos);
        dfs(nex,pos);
    }
    ot[pos] = counter;
}

void update(int u,int v,int val){
    //printf("u %d idbig %d v %d idbig %d\n",u,idbig[u],v,idbig[v]);
    u = idbig[u];
    v = idbig[v];
    if(kth(u,depth[u]) != kth(v,depth[v])) return;
    if(in[u] <= in[v] && in[v] <= ot[u]) swap(u,v);
    if(in[v] <= in[u] && in[u] <= ot[v]){
        update(in[u],val);
        v = anc[v][0];
        //printf("u %d v %d\n",u,v);
        update(in[v],-val);
    }
    else{
        int w = lca(u,v);
        update(in[u],val);
        update(in[v],val);
        update(in[w],-val);
        w = anc[w][0];
        update(in[w],-val);
    }
}

void query_vertex(int u){
    int uu = u;
    u = idbig[u];
    int res = query(ot[u]) - query(in[u] - 1);
    //printf("uu %d u %d res %d last %d\n",uu,u,res,last[uu]);
    ans += (res - last[uu]);
    if(ans >= MOD) ans -= MOD;
    last[uu] = res;
}

void init(){
    scanf("%d %d %d",&n,&m,&q);
    reset();
    for(int i = 1 ; i <= m ; i++){
        int u,v;
        scanf("%d %d",&u,&v);
        adj[u].pb(v);
        adj[v].pb(u);
    }
}

void build_tree(){
    for(int i = 1 ; i <= n ; i++)
        if(num[i] == -1)
            tarjan(i);
    for(int i = 1 ; i <= n ; i++)
        if(idbig[i] == 0)
            flood(i,i);
    for(auto it = bridge.begin() ; it != bridge.end() ; it++){
        int u = it -> fi;
        int v = it -> se;
        u = idbig[u];
        v = idbig[v];
        //printf("u to v %d %d\n",u,v);
        adjbig[u].pb(v);
    }                
    for(int i = 1 ; i <= n ; i++){
        if(idbig[i] == i && anc[i][0] == 0)
            dfs(i,0);
    }        
}

void solve(){
    for(int i = 0 ; i < q ; i++){
        char opt[5];
        scanf("%s",opt);
        if(opt[0] == 'T'){
            int u,v,val;
            scanf("%d %d %d",&u,&v,&val);
            update(u,v,val);
        }
        else{
            int u;
            scanf("%d",&u);
            query_vertex(u);
        }    
    }
    printf("%d\n",ans);
}

int main(){
    scanf("%d",&tc);
    for(int t = 1 ; t <= tc ; t++){
        init();
        build_tree();
        solve();
    }
    return 0;
}