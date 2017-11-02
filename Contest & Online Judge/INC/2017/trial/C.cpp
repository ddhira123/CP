#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second

const LL INF = 4e18;
const int N = 1e5 + 5;

LL dist[2][N];
vector<pii> adj[2][N];
int n, m, q;

void addEdge(int u,int v,int w) {
	adj[0][u].push_back({v,w});
	adj[1][v].push_back({u,w});
}

void dijkstra(int id,int s) {
	for(int i = 0 ; i < n ; i++)
		dist[id][i] = INF;

	priority_queue<pair<LL,int>> pq;
	dist[id][s] = 0;
	pq.push({0,s});

	while(!pq.empty()) {
		LL dis = -pq.top().fi;
		int now = pq.top().se;
		pq.pop();

		if(dist[id][now] != dis) continue;
		for(pii nex : adj[id][now]) {
			LL ndis = dis + nex.se;
			int nxt = nex.fi;

			if(dist[id][nxt] > ndis) {
				dist[id][nxt] = ndis;
				pq.push({-ndis,nxt});
			}
		}
	}
}

void read() {
	scanf("%d %d %d",&n,&m,&q);
	for(int i = 0 ; i < m ; i++) {
		int u, v, w;
		scanf("%d %d %d",&u,&v,&w);
		addEdge(u,v,w);
	}
}

void prepare() {
	dijkstra(0,0);
	dijkstra(1,n-1);
	assert(dist[0][n-1] != INF);
}

void solve() {
	for(int i = 0 ; i < q ; i++) {
		int u, v, w;
		scanf("%d %d %d",&u,&v,&w);
		if(dist[0][n-1] > dist[0][u] + w + dist[1][v])
			puts("YES");
		else
			puts("NO");
	}
}

void reset() {
	for(int i = 0 ; i < n ; i++) {
		adj[0][i].clear();
		adj[1][i].clear();
	}
}

int main() {
	int t = 1;
	//scanf("%d",&t);

	for(int tc = 1 ; tc <= t ; tc++) {
		//printf("Case #%d:\n",tc);
		read();
		prepare();
		solve();
		reset();
	}
	return 0;
}