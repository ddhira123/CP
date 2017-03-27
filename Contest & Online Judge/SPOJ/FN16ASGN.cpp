#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 5e3 + 5;
const int INF = 1e9;
const long long INFLL = 4e18;

int n, b, s, r;
long long dp[N][N];
int dist[N];
int distR[N];
vector<pair<int, int>> adj[N];
vector<pair<int, int>> adjR[N];
int val[N];
LL psum[N];

bool read() {
	if(scanf("%d %d %d %d", &n, &b, &s, &r) != 4) {
		return false;
	}

	for(int i = 0 ; i < r ; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v ,&w);
		adj[u].push_back({v, w});
		adjR[v].push_back({u, w});
	}

	return true;
}

void dijkstra() {
	for(int i = 1 ; i <= n ; i++)
		dist[i] = INF;
	dist[b+1] = 0;

	priority_queue<pair<int,int>> pq;
	pq.push({0, b+1});

	while(!pq.empty()) {
		int now = pq.top().second;
		int dis = -pq.top().first;

		pq.pop();
		if(dist[now] != dis) continue;

		for(pair<int,int> nex : adj[now]) {
			int node = nex.first;
			int ndis = dis + nex.second;

			if(ndis < dist[node]) {
				dist[node] = ndis;
				pq.push({-ndis, node});
			}
		}
	}
}

void dijkstraReverse() {
	for(int i = 1 ; i <= n ; i++)
		distR[i] = INF;
	distR[b+1] = 0;

	priority_queue<pair<int,int>> pq;
	pq.push({0, b+1});

	while(!pq.empty()) {
		int now = pq.top().second;
		int dis = -pq.top().first;

		pq.pop();
		if(distR[now] != dis) continue;

		for(pair<int,int> nex : adjR[now]) {
			int node = nex.first;
			int ndis = dis + nex.second;

			if(ndis < distR[node]) {
				distR[node] = ndis;
				pq.push({-ndis, node});
			}
		}
	}
}

void populate(int k, int l, int r,int optL, int optR) {
	if(l > r) return;
	int mid = (l + r) / 2;

	LL &ret = dp[k][mid];
	ret = INFLL;
	int best = optL;

	for(int i = max(optL, mid) ; i <= optR ; i++) {
		LL temp = dp[k-1][i+1] + 1ll * (i-mid) * (psum[i] - psum[mid-1]);
		if(temp <= ret) {
			ret = temp;
			best = i;
		} 
	}

	populate(k, l, mid-1, optL, best);
	populate(k, mid+1, r, best, optR);
}

LL solve() {
	dijkstra();
	dijkstraReverse();

	for(int i = 1 ; i <= b ; i++) {
		val[i] = dist[i] + distR[i];
		// printf("%d\n", val[i]);
	}
	sort(val + 1, val + b + 1);

	for(int i = 1 ; i <= b ; i++) {
		psum[i] = val[i] + psum[i-1];
		dp[0][i] = INFLL;
	}

	dp[0][b+1] = 0;
	for(int i = 1 ; i <= s ; i++) {
		dp[i][b+1] = INFLL;
		populate(i, 1, b, 1, b);
	}

	return dp[s][1];
}

void reset() {
	for(int i = 1 ; i <= n ; i++) {
		adj[i].clear();
		adjR[i].clear();
	}
}

int main() {
	while(read()) {
		printf("%lld\n", solve());
		reset();
	}
	return 0;
}