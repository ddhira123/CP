#include <bits/stdc++.h>
using namespace std;

const int MX = 2000;
const int N = 100005;
const int INF = (int)1e9;

#define fi first
#define se second
#define mp make_pair
#define pb push_back

typedef pair<int,int> pii;

map<string,int> compress;
int cnt;
int U[N],V[N],D[N];
vector<pii> adj[MX];
int dist[MX];
int pset[2 * N];
int tc,n;

int finds(int x){
    return x == pset[x] ? x : pset[x] = finds(pset[x]);
}

void join(int x,int y){
    x = finds(x);
    y = finds(y);
    if(x == y) return;
    pset[x] = y;
}

void init(){
    compress.clear();
    cnt = 0;
    cin >> n;
    for(int i = 0 ; i < n ; i++){
        string u,v;
        cin >> u >> v;
        int uu,vv;
        if(compress.count(u))
            uu = compress[u];
        else{
            compress[u] = uu = cnt++;
            pset[uu] = uu;
        }    
        if(compress.count(v))
            vv = compress[v];
        else{
            compress[v] = vv = cnt++;
            pset[vv] = vv;
        }    
        join(uu,vv);
        int d;
        cin >> d;
        //cout << uu << " " << vv << " " << d << "\n";
        U[i] = uu;
        V[i] = vv;
        D[i] = d;                
    }    
}

void solve(){
    for(int i = 0 ; i < cnt ; i++)
        if(finds(i) != finds(0)){
            cout << "INFINITE\n";
            return;
        }
    assert(cnt < MX);
    for(int i = 0 ; i < cnt ; i++){
        adj[i].clear();
    }        
    for(int i = 0 ; i < n ; i++){
        int u = U[i];
        int v = V[i];
        int d = D[i];
        adj[u].pb(mp(v,d));
        adj[v].pb(mp(u,d));
    }    
    int maks = 0;               
    for(int i = 0 ; i < cnt ; i++){
        priority_queue<pii,vector<pii>,greater<pii> > pq;
        for(int j = 0 ; j < cnt ; j++)
            dist[j] = INF;
        dist[i] = 0;
        pq.push(mp(0,i));    
        while(!pq.empty()){
            pii now = pq.top();
            pq.pop();
            if(dist[now.se] != now.fi) continue;
            maks = max(maks,now.fi);
            for(pii nxt : adj[now.se]){
                int nex = nxt.fi;
                int ncos = now.fi + nxt.se;
                if(ncos < dist[nex]){
                    dist[nex] = ncos;
                    pq.push(mp(ncos,nex));
                }
            }
        }
    }
    cout << maks << "\n";                        
}

int main(){
    ios_base::sync_with_stdio(0);
    cin >> tc;
    for(int t = 1 ; t <= tc ; t++){
        init();
        cout << "Case #" << t << ": ";
        solve(); 
    }
    return 0;
}