#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int LOG = 17;

int depth[N];
int anc[N][LOG];
int BIT[N];
int in[N], ot[N];
bool udah[N];
int n;
vector<int> chld[N];
int cnt;

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

void build(int prv,int now) {
	depth[now] = depth[prv] + 1;
	anc[now][0] = prv;

	for(int i = 1 ; (1 << i) <= depth[now] ; i++) {
		int papa = anc[now][i-1];
		anc[now][i] = anc[papa][i-1];
	}
}

void dfs(int now) {
	in[now] = ++cnt;
	for(int nex : chld[now]) {
		//printf("par %d %d\n",nex,now);
		build(now,nex);
		dfs(nex);
	}
	ot[now] = cnt;
}

int getLCA(int u,int v) {
	if(depth[u] < depth[v]) swap(u,v);
	int diff = depth[u] - depth[v];
	for(int i = 0 ; diff > 0 ; i++)
		if(diff & (1 << i)) {
			diff -= (1 << i);
			u = anc[u][i];
		}

	if(u == v) return u;	
	for(int i = LOG - 1 ; i >= 0 ; i--)
		if(depth[u] >= (1 << i) && anc[u][i] != anc[v][i]) {
			u = anc[u][i];
			v = anc[v][i];
		}

	return anc[u][0];	
}

void updater(int x) {
	update(in[x],1);
	update(ot[x] + 1,-1);
	udah[x] = 1;
}

int answer(int u,int v) {
	int lca = getLCA(u,v);
	int ret = depth[u] + depth[v] - 2*depth[lca];
	ret -= (query(in[u]) + query(in[v]) - 2*query(in[lca]));
	return ret;
}

int main() {
	scanf("%d",&n);
	for(int i = 2 ; i <= n ; i++) {
		int x; scanf("%d",&x);
		chld[x].push_back(i);
	}
	dfs(1);
	int q; scanf("%d",&q);
	for(int i = 0 ; i < q ; i++) {
		int opt; scanf("%d",&opt);
		if(opt == 2) {
			int u; scanf("%d",&u);
			updater(u);
		}
		else {
			int u,v; scanf("%d %d",&u,&v);
			printf("%d\n",answer(u,v));
		}
	}
	return 0;
}