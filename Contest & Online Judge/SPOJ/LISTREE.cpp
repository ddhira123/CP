#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

struct SegmentTree {
	int tree[4*N];
	int n;

	SegmentTree() {
		memset(tree, 0, sizeof tree);
	}

	void update(int x,int val) {
		update(1, 1, n, x, val);
	}

	void update(int id, int l, int r, int x, int val) {
		if(l == r) {
			tree[id] = val;
		} else {
			int m = (l + r) / 2;
			int chld = id << 1;

			if(x <= m)	update(chld, l, m, x ,val);
			else		update(chld+1, m+1, r, x, val);

			tree[id] = max(tree[chld], tree[chld+1]);
		}
	}

	int query(int l, int r) {
		return query(1, 1, n, l, r);
	}

	int query(int id, int l, int r, int x, int y) {
		if(x <= l && r <= y) {
			return tree[id];
		} else {
			int m = (l + r) / 2;
			int chld = id << 1;

			int ret = 0;
			if(x <= m)	ret = max(ret, query(chld, l, m, x, y));
			if(y > m)	ret = max(ret, query(chld+1, m+1, r, x, y));
			return ret;
		}
	}
};

SegmentTree upTree, downTree;
int tempUp[N], tempDown[N];

vector<int> adj[N];
int in[N], ot[N], inve[N];
int sz[N];
int timeStamp;
int n, ans;

void dfs(int now, int prv) {
	in[now] = ++timeStamp;
	inve[timeStamp] = now;
	sz[now] = 1;

	for(int nex : adj[now]) {
		if(nex == prv) continue;
		dfs(nex, now);
		sz[now] += sz[nex];
	}
	ot[now] = timeStamp;
}

void solve(int now, int prv, int keep) {
	// printf("%d %d %d\n", now, prv, keep);
	int heavy = -1;
	for(int nex : adj[now]) {
		if(nex == prv) continue;
		if(heavy == -1 || sz[nex] > sz[heavy])
			heavy = nex;
	}

	for(int nex : adj[now]) {
		if(nex == prv || nex == heavy) continue;
		solve(nex, now, 0);
	}

	if(heavy != -1) {
		solve(heavy, now, 1);
	}

	for(int nex : adj[now]) {
		if(nex == prv || nex == heavy) continue;
		int tUp = upTree.query(1, now) + 1;
		int tDown = downTree.query(now, n) + 1;

		for(int i = in[nex] ; i <= ot[nex] ; i++) {
			int idx = inve[i];
			// printf("process %d\n", idx);

			// skip
			ans = max(ans, tempUp[idx] + downTree.query(idx, n));
			ans = max(ans, tempDown[idx] + upTree.query(1, idx));

			// use
			if(idx > now) {
				ans = max(ans, tUp + tempDown[idx]);
			} else {
				ans = max(ans, tDown + tempUp[idx]);	
			}
		}

		for(int i = in[nex] ; i <= ot[nex] ; i++) {
			int idx = inve[i];

			upTree.update(idx, tempUp[idx]);
			downTree.update(idx, tempDown[idx]);
		}
	}

	tempUp[now] = upTree.query(1, now) + 1;
	tempDown[now] = downTree.query(now, n) + 1;
	ans = max(ans, tempUp[now]);
	ans = max(ans, tempDown[now]);

	upTree.update(now, tempUp[now]);
	downTree.update(now, tempDown[now]);

	if(keep == 0) {
		for(int i = in[now] ; i <= ot[now] ; i++) {
			int idx = inve[i];

			upTree.update(idx, 0);
			downTree.update(idx, 0);
		}
	}
}

void prepare() {
	dfs(1, 0);
	upTree.n = n;
	downTree.n = n;
}

void reset() {
	ans = 0;
	for(int i = 1 ; i <= n ; i++)
		adj[i].clear();
	timeStamp = 0;
}

void read() {
	scanf("%d", &n);

	for(int i = 1 ; i < n ; i++) {
		int u, v;
		scanf("%d %d",&u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

int main() {
	int t; scanf("%d", &t);

	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		prepare();
		solve(1, 0, 0);
		printf("%d\n", ans);
		reset();
	}
	return 0;
}