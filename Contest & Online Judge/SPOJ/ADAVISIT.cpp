#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;

int n;
vector<int> adj[N];
int sum[N];
int par[N];

int pset[N];
int color[N];

void init() {
	for(int i = 1 ; i <= n ; i++) {
		pset[i] = i;
		color[i] = 0;
	}
}

int finds(int x) {
	return pset[x] == x ? x : pset[x] = finds(pset[x]);
}

void dfs(int now, int prv) {
	par[now] = prv;

	for(int nex : adj[now]) {
		if(nex == prv) continue;
		dfs(nex, now);
		pset[finds(nex)] = now;
	}

	color[now] = 1;
	if(color[now-1] == 1) {
		sum[now]++;
		sum[now-1]++;
		sum[finds(now-1)]--;
		sum[par[finds(now-1)]]--;
	}
	if(color[now+1] == 1) {
		sum[now]++;
		sum[now+1]++;
		sum[finds(now+1)]--;
		sum[par[finds(now+1)]]--;
	}
}

void apply(int now) {
	for(int nex : adj[now]) {
		if(nex == par[now]) continue;
		apply(nex);
		sum[now] += sum[nex];
	}
}

void read() {
	scanf("%d", &n);
	for(int i = 1 ; i < n ; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

void prepare() {
	init();
	dfs(1, 0);
}

void solve() {
	apply(1);
	for(int i = 1 ; i <= n ; i++)
		printf("%d\n", sum[i]);
}

int main() {
	read();
	prepare();
	solve();
	return 0;
}