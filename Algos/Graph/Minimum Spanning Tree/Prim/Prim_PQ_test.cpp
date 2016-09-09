// SPOJ - MST
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 1e5 + 5;
const int M = 1e5 + 5;
const int INF = 1e9;

vector<pii> adj[N];
bool taken[N];
int n, m;

long long primPriorityQueue() {
	priority_queue<pii,vector<pii>,greater<pii>> pq;

	for(int i = 1 ; i <= 1 ; i++) {
		pq.push({INF,i});
	}

	long long ans = 0;
	while(!pq.empty()) {
		pii now = pq.top();
		pq.pop();

		if(taken[now.se]) continue;
		if(now.fi == INF) now.fi = 0;

		taken[now.se] = 1;
		ans += now.fi;

		for(pii nex : adj[now.se]) {
			pq.push({nex.se,nex.fi});
		}
	}

	return ans;
}

void read() {
	scanf("%d %d",&n,&m);
	for(int i = 0 ; i < m ; i++) {
		int u, v, c;
		scanf("%d %d %d",&u,&v,&c);

		adj[u].push_back({v,c});
		adj[v].push_back({u,c});
	}
}

int main() {
	read();
	printf("%lld\n",primPriorityQueue());
	return 0;
}