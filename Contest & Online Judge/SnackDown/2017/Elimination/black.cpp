#include <bits/stdc++.h>
using namespace std;

const int N = 5005;

int gMax[N], gMin[N];
int dpMax[N][N], dpMin[N][N];
int color[N];

int size[N];
int maxSize[N];
int blocked[N];

int in[N], ot[N];
int inve[N];
int cnt;

int n, q;

vector<int> adj[N];
vector<int> seen;

void dfs_tin(int now, int prv) {
	in[now] = ++cnt;
	inve[cnt] = now;
	for(int nex : adj[now]) {
		if(nex == prv || blocked[nex]) continue;
		dfs_tin(nex, now);
	}
	ot[now] = cnt;
}

void dfs_size(int now, int prv) {
	seen.push_back(now);

	maxSize[now] = 0;
	size[now] = 1;

	for(int nex : adj[now]) {
		if(nex == prv || blocked[nex]) continue;

		dfs_size(nex, now);
		size[now] += size[nex];
		maxSize[now] = max(maxSize[now], size[nex]);
	}
}

void work(int root) {
	cnt = 0;
	dfs_tin(root, -1);

	for(int i = 1 ; i <= cnt+1 ; i++)
		for(int j = 0 ; j <= cnt ; j++) {
			dpMax[i][j] = -N;
			dpMin[i][j] = N;
		}

	dpMin[2][color[root]] = 1;
	dpMax[2][color[root]] = 1;

	for(int i = 2 ; i <= cnt ; i++) {
		int node = inve[i];
		int nxt = ot[node];

		for(int j = 0 ; j <= cnt ; j++) {
			// skip
			dpMin[nxt+1][j] = min(dpMin[nxt+1][j], dpMin[i][j]);
			dpMax[nxt+1][j] = max(dpMax[nxt+1][j], dpMax[i][j]);
			// pake
			dpMin[i+1][j + color[node]] = min(dpMin[i+1][j + color[node]], dpMin[i][j] + 1);
			dpMax[i+1][j + color[node]] = max(dpMax[i+1][j + color[node]], dpMax[i][j] + 1);
		}
	}

	for(int j = 0 ; j <= cnt ; j++) {
		gMin[j] = min(gMin[j], dpMin[cnt+1][j]);
		gMax[j] = max(gMax[j], dpMax[cnt+1][j]);
	}
}

void centroid(int now) {
	seen.clear();
	dfs_size(now, 0);
	int root = now;

	for(int x : seen) {
		maxSize[x] = max(maxSize[x], size[now] - size[x]);

		if(maxSize[x] < maxSize[root]) {
			root = x;
		}
	}

	work(root);

	blocked[root] = 1;
	for(int nex : adj[root]) {
		if(blocked[nex]) continue;

		centroid(nex);
	}
}

void read() {
	scanf("%d %d", &n, &q);
	for(int i = 1 ; i < n ; i++) {
		int u, v;

		scanf("%d %d", &u, &v);

		adj[u].push_back(v);
		adj[v].push_back(u);
		// printf("add %d %d\n", u, v);
	}

	for(int i = 1 ; i <= n ; i++) {
		scanf("%d", color + i);
		// printf("%d color %d\n", i, color[i]);
	}
}

void work() {
	for(int i = 0 ; i <= n ; i++) {
		gMin[i] = N;
		gMax[i] = -N;
		blocked[i] = 0;
	}

	centroid(1);
	for(int i = 0 ; i < q ; i++) {
		int s, b;
		scanf("%d %d", &s, &b);

		if(gMin[b] <= s && s <= gMax[b]) {
			puts("Yes");
		} else {
			puts("No");
		}
	}
}

void reset() {
	for(int i = 0 ; i <= n ; i++) {
		adj[i].clear();
	}
}

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		work();
		reset();
	}
	return 0;
}