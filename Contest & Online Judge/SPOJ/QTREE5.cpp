#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int N = 100005;
const int LOG = 17;
const int INF = 1000000000;

vector<int> adj[N];
int anc[N][LOG];
int depth[N];
int par[N]; // in centroid tree
int sz[N]; // root helper
int worst[N];
vector<int> inside;
bool blocked[N]; // already in tree
multiset<int> s[N];
bool active[N];
int n,m;

void build(int prv,int now){
    depth[now] = depth[prv] + 1;
    anc[now][0] = prv;
    for(int i = 1 ; (1 << i) <= depth[now] ; i++){
        int papa = anc[now][i - 1];
        int grandpa = anc[papa][i - 1];
        anc[now][i] = grandpa;
    }
}

void dfs(int prv,int now){
    for(int i = 0 ; i < adj[now].size() ; i++){
        int nxt = adj[now][i];
        if(nxt == prv) continue;
        build(now,nxt);
        dfs(now,nxt);
    }
}

void dfsroot(int prv,int now){
    sz[now] = 1;
    worst[now] = 0;
    inside.push_back(now);
    for(int i = 0 ; i < adj[now].size() ; i++){
        int nxt = adj[now][i];
        if(nxt == prv || blocked[nxt]) continue;
        dfsroot(now,nxt);
        worst[now] = max(worst[now],sz[nxt]);
        sz[now] += sz[nxt];
    }
}

void centroid(int prv,int now){
    inside.clear();
    dfsroot(0,now);
    int root = now;
    for(int i = 0 ; i < inside.size() ; i++){
        int pos = inside[i];
        worst[pos] = max(worst[pos],sz[now] - sz[pos]);
        if(worst[pos] < worst[root]){
            root = pos;
        }
    }
    par[root] = prv;
    blocked[root] = 1;
    for(int i = 0 ; i < adj[root].size() ; i++){
        int nxt = adj[root][i];
        if(!blocked[nxt])
            centroid(root,nxt);
    }
}

int LCA(int u,int v){
    if(depth[u] < depth[v]) swap(u,v);
    int diff = depth[u] - depth[v];
    for(int i = 0 ; diff > 0 ; i++)
        if(diff & (1 << i)){
            u = anc[u][i];
            diff ^= (1 << i);
        }
    if(u == v) return v;
    for(int i = LOG - 1 ; i >= 0 ; i--)
        if(depth[u] >= (1 << i) && anc[u][i] != anc[v][i]){
            u = anc[u][i];
            v = anc[v][i];
        }
    return anc[u][0];    
}

int dist(int u,int v){
    return depth[u] + depth[v] - 2 * depth[LCA(u,v)];
}

void add(int now){
    int st = now;
    while(now){
        s[now].insert(dist(st,now));
        now = par[now];
    }
}

void remove(int now){
    int st = now;
    while(now){
        multiset<int>::iterator it = s[now].find(dist(st,now));
        s[now].erase(it);
        now = par[now];
    }
}

int query(int now){
    int st = now;
    int ret = INF;
    while(now){
        //printf("st %d now %d\n",st,now);
        if(!s[now].empty()){
            //printf("ada %d\n",*s[now].begin());
            ret = min(ret,*s[now].begin() + dist(st,now));
        }    
        now = par[now];
    }
    return ret;
}

void init(){
    scanf("%d",&n);
    for(int i = 1 ; i < n ; i++){
        int u,v;
        scanf("%d %d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0,1);
    centroid(0,1);
}

void solve(){
    scanf("%d",&m);
    for(int i = 1 ; i <= m ; i++){
        int opt,u;
        scanf("%d %d",&opt,&u);
        if(opt == 0){
            if(active[u])
                remove(u);
            else
                add(u);    
            active[u] ^= 1;
        }
        else{
            int ans = query(u);
            if(ans == INF) ans = -1;
            printf("%d\n",ans);
        }
    }
}

int main(){
    init();
    solve();
    return 0;
}