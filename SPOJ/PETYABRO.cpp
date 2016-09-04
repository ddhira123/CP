#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back

typedef long long LL;
typedef pair<int,int> pii;

const int N = 100005;
const LL INF = (LL)1e18;

struct edge{
    int u,v,w;
    
    edge(int _u = 0,int _v = 0,int _w = 0){
        u = _u;
        v = _v;
        w = _w;
    }
    
    bool operator <(edge other) const{
        return w < other.w;
    }
};

vector<pii> adj[N];
LL dist[N];
vector<edge> elist;
int pset[N];
int saiz[N];
int n,m;

int finds(int x){
    return x == pset[x] ? x : pset[x] = finds(pset[x]);
}

void join(int u,int v){
    u = finds(u);
    v = finds(v);
    if(u == v) return;
    pset[v] = u;
    saiz[u] += saiz[v];
}

void init(){
    scanf("%d %d",&n,&m);
    pset[0] = 0;
    saiz[0] = 1;
    for(int i = 1 ; i <= n ; i++){
        int x;
        scanf("%d",&x);
        if(x)
            adj[0].pb({i,0});
        pset[i] = i;
        saiz[i] = 1;    
    }
    for(int i = 1 ; i <= m ; i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        adj[u].pb({v,w});
        adj[v].pb({u,w});
    }
}

priority_queue<pair<LL,int> > pq;

void dijkstra(){
    for(int i = 1 ; i <= n ; i++)
        dist[i] = INF;
    pq.push({0,0});
    while(!pq.empty()){
        LL dis = -pq.top().fi;
        int now = pq.top().se;
        pq.pop();
        if(dis != dist[now]) continue;
        for(pii nex : adj[now]){
            int nxt = nex.fi;
            LL ndis = dis + nex.se;
            if(ndis < dist[nxt]){
                dist[nxt] = ndis;
                pq.push({-ndis,nxt});
            }        
        }
    }        
}

void build(){
    for(int i = 0 ; i <= n ; i++)
        for(pii nex : adj[i]){
            int nxt = nex.fi;
            LL ndis = dist[i] + nex.se;
            if(dist[nxt] == ndis)
                elist.pb({i,nxt,nex.se});
        }
}

void solve(){
    sort(elist.begin(),elist.end());
    LL res = 0;
    for(int i = 0 ; i < elist.size() && saiz[finds(0)] < n + 1 ; i++){
        int u = elist[i].u;
        int v = elist[i].v;
        int w = elist[i].w;
        if(finds(u) != finds(v)){
            res += w;
            join(u,v);
        }
    }
    if(saiz[finds(0)] != n + 1)
        puts("impossible");
    else
        printf("%lld\n",res);    
}

int main(){
    init();
    dijkstra();
    build();
    solve();
    return 0;
}
