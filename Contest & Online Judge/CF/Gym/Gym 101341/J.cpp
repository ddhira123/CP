// WA
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

vector<int> adj[N];
int depth[N];
int par[N];
bool active[N];
int lst = -1;
int n;

void read() {
	scanf("%d", &n);
	for(int i = 1 ; i < n ; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

void make(int a) {
	int cur = a;
	if(lst == -1) {
		lst = cur;
	}
	while(cur != lst) {
		if(depth[cur] > depth[lst]) {
			active[cur] = 1;
			cur = par[cur];
		} else {
			active[lst] = 1;
			lst = par[lst];
		}
	}
	active[cur] = 1;
	lst = a;
}

void dfs(int now) {
	if(adj[now].size() > 3) {
		make(now);
	}
	for(int nex : adj[now]) {
		if(nex == par[now]) continue;
		depth[nex] = depth[now]+1;
		par[nex] = now;
		dfs(nex);
	}
}

bool can() {
	for(int i = 1 ; i <= n ; i++) {
		int lol = 0;
		for(int x : adj[i])
			lol += active[x];
		if(lol > 2)
			return false;
	}
	return true;
}

int main() {
	read();
	dfs(1);
	printf("%s\n", can() ? "YES" : "NO");
	return 0;
}
