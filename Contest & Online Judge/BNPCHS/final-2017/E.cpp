#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const long long INF = 4e18;

long long dist_dragon[N];
long long dist_dragon_2[N];
bool dragon[N];
bool fruit[N];

long long dist_bondol[N];

vector<pair<int,int>> adj[N];

int s, d;
int n, m;

void reset() {
	for(int i = 0 ; i < N ; i++) {
		dist_dragon[i] = dist_bondol[i] = INF;
		dragon[i] = fruit[i] = 0;
		adj[i].clear();
	}
}

void dijkstra_bondol() {
	dist_bondol[s] = 0;
	priority_queue<pair<long long,int>> pq;
	pq.push({0, s});

	while(!pq.empty()) {
		auto now = pq.top();
		pq.pop();

		if(-now.first != dist_bondol[now.second]) continue;

		for(pair<int,int> nex : adj[now.second]) {
			int nxt = nex.first;
			long long ncos = -now.first + nex.second;

			if(ncos < dist_bondol[nxt]) {
				dist_bondol[nxt] = ncos;
				pq.push({-ncos, nxt});
			}
		}
	}
}

void dijkstra_dragon() {
	priority_queue<pair<long long,int>> pq;

	for(int i = 1 ; i <= n ; i++)
		if(dragon[i]) {
			dist_dragon[i] = 0;
			pq.push({0, i});
		}

	while(!pq.empty()) {
		auto now = pq.top();
		pq.pop();

		if(-now.first != dist_dragon[now.second]) continue;

		for(pair<int,int> nex : adj[now.second]) {
			int nxt = nex.first;
			long long ncos = -now.first + nex.second;

			if(ncos < dist_dragon[nxt]) {
				dist_dragon[nxt] = ncos;
				pq.push({-ncos, nxt});
			}
		}
	}

	// twice the fun
	for(int i = 1 ; i <= n ; i++)
		if(fruit[i]) {
			dist_dragon_2[i] = dist_dragon[i];
			pq.push({-dist_dragon[i], i});
		} else {
			dist_dragon_2[i] = INF;
		}

	while(!pq.empty()) {
		auto now = pq.top();
		pq.pop();

		if(-now.first != dist_dragon_2[now.second]) continue;

		for(pair<int,int> nex : adj[now.second]) {
			int nxt = nex.first;
			long long ncos = -now.first + nex.second / 2;

			if(ncos < dist_dragon_2[nxt]) {
				dist_dragon_2[nxt] = ncos;
				pq.push({-ncos, nxt});
			}
		}
	}

	for(int i = 1 ; i <= n ; i++) {
		dist_dragon[i] = min(dist_dragon[i], dist_dragon_2[i]);
	}
}

void read() {
	scanf("%d %d", &n, &m);
	for(int i = 0 ; i < m ; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		w *= 2;

		adj[u].push_back({v, w});
		adj[v].push_back({u, w});
	}

	int x;
	scanf("%d", &x);
	for(int i = 0 ; i < x ; i++) {
		int y; scanf("%d", &y);
		dragon[y] = true;
	}

	scanf("%d", &x);
	for(int i = 0 ; i < x ; i++) {
		int y; scanf("%d", &y);
		fruit[y] = true;
	}

	scanf("%d %d", &s, &d);
}

long long solve() {
	dijkstra_bondol();
	dijkstra_dragon();

	// printf("%lld %lld\n", dist_bondol[d], dist_dragon[d]);

	if(dist_bondol[d] == INF) {
		return -2;
	}
	if(dist_bondol[d] >= dist_dragon[d]) {
		return -2;
	}

	return dist_bondol[d];
}

int main() {
	int t; scanf("%d", &t);
	for(int tc = 1 ; tc <= t; tc++) {
		reset();
		read();
		printf("Kasus #%d: %lld\n", tc, solve() / 2);
	}
	return 0;
}