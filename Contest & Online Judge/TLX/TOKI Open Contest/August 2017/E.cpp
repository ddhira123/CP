#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> adj[N];
vector<int> adjBig[N];
vector<pair<int,int>> bridge;

int low[N], num[N];
int val[N];
int pset[N];
int longest[N];

int n, m;

void init() {
	for(int i = 1 ; i <= n ; i++) {
		pset[i] = -val[i];
		low[i] = num[i] = -1; 
	}
}

int finds(int x) {
	return pset[x] <= 0 ? x : pset[x] = finds(pset[x]);
}

void join(int x, int y) {
	x = finds(x);
	y = finds(y);

	if(x != y) {
		pset[x] += pset[y];
		pset[y] = x;
	}
}

void tarjan(int prv, int now) {
	static int cnt = 1;
	low[now] = num[now] = cnt++;

	for(int nex : adj[now]) {
		if(low[nex] == -1) {
			tarjan(now, nex);

			if(low[nex] > num[now]) {
				bridge.push_back({now, nex});
			} else {
				join(now, nex);
			}

			low[now] = min(low[now], low[nex]);
		} else if(prv != nex) {
			low[now] = min(low[now], num[nex]);
		}
	}
}

void read() {
	scanf("%d %d", &n, &m);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d", val + i);
	}
	for(int i = 1 ; i <= m ; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

void prepare() {
	init();
	tarjan(-1, 1);

	for(pair<int,int> x : bridge) {
		int u = finds(x.first);
		int v = finds(x.second);
		// printf("bridge %d %d\n", u, v);
		adjBig[u].push_back(v);
		adjBig[v].push_back(u);
	}
}

int dfs_solve(int prv, int now) {
	assert(1 <= now && now <= n);
	assert(pset[now] < 0);
	
	int mx = 0;
	int ret = 0;

	for(int nex : adjBig[now]) {
		if(nex == prv) continue;
		ret = max(ret, dfs_solve(now, nex));
		ret = max(ret, mx - pset[now] + longest[nex]);
		mx = max(mx, longest[nex]);
	}

	ret = max(ret, mx - pset[now]);
	longest[now] = mx - pset[now];

	return ret;
}

int solve() {
	return dfs_solve(-1, finds(1));
}

void tes() {
	for(int i = 1 ; i <= n ; i++) {
		assert(low[i] != -1);
		assert(1 <= val[i] && val[i] <= 10000);
	}
}

int main() {
	read();
	prepare();
	tes();
	printf("%d\n", solve());
	return 0;
}