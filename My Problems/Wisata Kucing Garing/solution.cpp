#include <bits/stdc++.h>
using namespace std;

const int MAX_NODE = 10000;
const int MAX_VAL = 1e6;
const int MAX_FACTOR = 240;

int idx[MAX_VAL+5];
int val[MAX_NODE+5];
bool vis[MAX_NODE+5][MAX_FACTOR+5];
int factor_count = 0;

int n, m;
vector<int> adj[MAX_NODE+5];

void read() {
	scanf("%d %d", &n, &m);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d", val + i);
	for(int i = 0 ; i < m ; i++) {
		int u, v;
		scanf("%d %d", &u, &v);

		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

void prepare() {
	for(int i = 1 ; i <= val[1] ; i++)
		if(val[1] % i == 0) {
			idx[i] = ++factor_count;
		}
}

void dfs(int now, int fpb) {
	if(vis[now][idx[fpb]]) {
		return;
	}

	vis[now][idx[fpb]] = 1;

	for(int nex : adj[now]) {
		int nex_fpb = __gcd(fpb, val[nex]);

		dfs(nex, nex_fpb);
	}
}

int solve() {
	dfs(1, val[1]);

	for(int i = MAX_VAL ; i >= 1 ; i--)
		if(idx[i] > 0 && vis[n][idx[i]]) {
			return i;
		}
}

int main() {
	read();
	prepare();
	printf("%d\n", solve());
	return 0;
}