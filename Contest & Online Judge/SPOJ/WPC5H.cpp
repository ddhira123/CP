#include <bits/stdc++.h>
using namespace std;

const int N = 50005;
const int LOG = 16;

vector<int> adj[N];
int anc[N][LOG];
int BIT[N];
int in[N], ot[N];
int cnt;
int depth[N];
int n,q;

void update(int x,int val) {
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

int query(int lo,int hi) {
	return query(hi) - query(lo - 1);
}

void build(int now,int prv) {
	anc[now][0] = prv;
	depth[now] = depth[prv] + 1;
	for(int i = 1 ; (1 << i) <= depth[now] ; i++) {
		int par = anc[now][i - 1];
		anc[now][i] = anc[par][i - 1];
	}
}

void dfs(int now,int prv) {
	in[now] = ++cnt;
	for(int i = 0 ; i < adj[now].size() ; i++) {
		int nex = adj[now][i];
		if(nex == prv) continue;
		build(nex,now);
		dfs(nex,now);
	}
	ot[now] = cnt;
}

int getLCA(int u,int v) {
	if(depth[u] < depth[v]) swap(u,v);
	int diff = depth[u] - depth[v];
	for(int i = 0 ; diff ; i++)
		if(diff & (1 << i)) {
			u = anc[u][i];
			diff -= (1 << i);
		}

	if(u == v) return u;	
	for(int i = LOG - 1 ; i >= 0 ; i--)
		if((1 << i) <= depth[u] && anc[u][i] != anc[v][i]) {
			u = anc[u][i];
			v = anc[v][i];
		}

	return anc[u][0];	
}

void updater(int u,int v,int k) {
	int lca = getLCA(u,v);
	update(in[u],k);
	update(in[v],k);
	update(in[lca],-k);
	lca = anc[lca][0];
	if(lca != 0) 
		update(in[lca],-k);
}

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i < n ; i++) {
		int u,v;
		scanf("%d %d",&u,&v);
		u++; v++;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

void solve() {
	dfs(1,0);
	scanf("%d",&q);
	for(int i = 0 ; i < q ; i++) {
		int a,b,k;
		scanf("%d %d %d",&a,&b,&k);
		a++; b++;
		if(k == -1)
			printf("%d %d\n",query(in[a],ot[a]), query(in[b],ot[b]));
		else
			updater(a,b,k);
	}
}

void reset() {
	for(int i = 0 ; i <= n ; i++) {
		BIT[i] = 0;
		adj[i].clear();
	}
	cnt = 0;
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		solve();
		reset();
	}
	return 0;
}