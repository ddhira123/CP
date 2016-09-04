#include <bits/stdc++.h>
using namespace std;

const int RANK = 10;
const int N = 30000;
const int INF = (int)1e9;

typedef pair<int,int> pii;
#define fi first
#define se second
#define pb push_back

vector<int> vertice[RANK + 1];
vector<pii> adj[N + 1];

int dist[N + 1]; // helper for current dijkstra
int prevDist[N + 1]; // for restoring dijkstra from previous rank
int best[N + 1]; // helper for updating dist later
int n,m;

void reset(){
	for(int i = 1 ; i <= n ; i++){
		dist[i] = prevDist[i] = best[i] = INF;
		adj[i].clear();
	}
	for(int i = 1 ; i <= RANK ; i++)
		vertice[i].clear();
}

void solve(){
	int ans = 0;
	for(int i = RANK ; i >= 1 ; i--){
		for(int v : vertice[i]){
			vector<int> seen;
			priority_queue<pii> pq;
			dist[v] = 0;
			pq.push({0,v});
			while(!pq.empty()){
				pii now = pq.top();
				pq.pop();
				now.fi = -now.fi;
				if(dist[now.se] != now.fi) continue;
				
				best[now.se] = min(best[now.se],now.fi);
				seen.pb(now.se);
				ans++;
				
				for(pii nex : adj[now.se]){
					int nxt = nex.fi;
					int ncos = now.fi + nex.se;
					if(ncos < dist[nxt]){
						dist[nxt] = ncos;
						pq.push({-ncos,nxt});
					}
				}
			}
			for(int u : seen)
				dist[u] = prevDist[u];
		}
		for(int j = 1 ; j <= n ; j++){
			dist[j] = prevDist[j] = best[j];
		}
	}
	printf("%d\n",ans);
}

void init(){
	for(int i = 1 ; i <= n ; i++){
		int rank;
		scanf("%d",&rank);
		vertice[rank].pb(i);
	}
	for(int i = 1 ; i <= m ; i++){
		int u,v,cost;
		scanf("%d %d %d",&u,&v,&cost);
		adj[u].pb({v,cost});
		adj[v].pb({u,cost});
	}
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d %d",&n,&m);
		reset();
		init();
		solve();
	}
	return 0;
}
