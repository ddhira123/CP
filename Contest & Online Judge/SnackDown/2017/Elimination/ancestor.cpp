#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

vector<int> adj[N], adj2[N];
int in[N], ot[N];
int BIT[N];
int n;
int ans[N];
int cnt;

void update(int x, int val) {
	for(; x <= n ; x += x & -x)
		BIT[x] += val;
}

int query(int x) {
	int ret = 0;
	while(x) {
		ret += BIT[x];
		x -= x & -x;
	}
	return ret;
}

inline void dfs(int prv, int now) {
	in[now] = ++cnt;
	for(int nex : adj[now]) {
		if(nex == prv) continue;
		dfs(now, nex);
	}
	ot[now] = cnt;
}

inline void solve(int prv, int now) {
	ans[now] = query(in[now]);
	update(in[now], 1);
	update(ot[now]+1, -1);

	for(int nex : adj2[now]) {
		if(nex == prv) continue;
		solve(now, nex);
	}

	update(in[now], -1);
	update(ot[now]+1, 1);
}

void read() {
	scanf("%d", &n);

	for(int i = 1 ; i < n ; i++) {
		int u, v;
		scanf("%d %d", &u, &v);

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for(int i = 1 ; i < n ; i++) {
		int u, v;
		scanf("%d %d", &u, &v);

		adj2[u].push_back(v);
		adj2[v].push_back(u);
	}
}

void work() {
	dfs(0, 1);
	solve(0, 1);

	for(int i = 1 ; i <= n ; i++)
		printf("%d%c", ans[i], i == n ? '\n' : ' ');
}

void reset() {
	cnt = 0;
	for(int i = 1 ; i <= n ; i++) {
		adj[i].clear();
		adj2[i].clear();
	}
}

int main() {
	int t; scanf("%d", &t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		work();
		reset();
	}
	return 0;
}