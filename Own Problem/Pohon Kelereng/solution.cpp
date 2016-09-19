#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 100005;
const int LOG = 18;

int anc[N][LOG];
int depth[N];
int in[N], ot[N];
int inve[N];
int cnt;

int val[N];
set<pii> active;
bool toggled[N];

long long BIT[N];

vector<int> chld[N];

int n,q;

bool inRange(int lo,int x,int hi) {
	return lo <= x && x <= hi;
}

void update(int x,long long val) {
	if(x == 0) return;
	for(; x <= n ; x += x & -x)
		BIT[x] += val;
}

long long query(int x) {
	long long res = 0;
	while(x) {
		res += BIT[x];
		x -= x & -x;
	}
	return res;
}

int getLCA(int u,int v) {
	if(depth[u] < depth[v]) swap(u,v);

	int diff = depth[u] - depth[v];
	for(int i = 0 ; diff ; i++)
		if(diff & (1<<i)) {
			diff -= (1<<i);
			u = anc[u][i];
		}

	if(u == v) return u;
	for(int i = LOG - 1 ; i >= 0 ; i--)
		if(depth[u] >= (1<<i) && anc[u][i] != anc[v][i]) {
			u = anc[u][i];
			v = anc[v][i];
		}	

	return anc[u][0];	
}

void build(int par,int now) {
	anc[now][0] = par;
	depth[now] = depth[par] + 1;
	for(int i = 1 ; (1 << i) <= depth[now] ; i++) {
		int papa = anc[now][i - 1];
		int grandpa = anc[papa][i - 1];
		anc[now][i] = grandpa;
	}
}

void dfs(int now) {
	in[now] = ++cnt;
	inve[cnt] = now;

	for(int nex : chld[now]) {
		build(now,nex);
		dfs(nex);
	}

	ot[now] = cnt;
}

void init() {
	scanf("%d %d",&n,&q);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",&val[i]);
	for(int i = 2 ; i <= n ; i++) {
		int papa;
		scanf("%d",&papa);
		chld[papa].push_back(i);
	}

	dfs(1);
}

void addPath(int v) {
	int kiri = -1, kanan = n + 1;
	pii cur = {val[v],in[v]};

	auto it = active.lower_bound(cur);

	if(it != active.end()) {
		pii temp = *it;
		if(temp.fi == val[v])
			kanan = temp.se;
	}
	if(it != active.begin()) {
		it--;
		pii temp = *it;
		if(temp.fi == val[v])
			kiri = temp.se;
	}

	active.insert(cur);
	
	int now = 0;
	if(kiri != -1) {
		kiri = inve[kiri];
		now = getLCA(v,kiri);
	}
	if(kanan != n+1) {
		kanan = inve[kanan];
		int lca = getLCA(v,kanan);
		if(depth[lca] > depth[now])
			now = lca;
	}

	update(in[v],val[v]);
	update(in[now],-val[v]);	
}

void removePath(int v) {
	int kiri = -1, kanan = n + 1;
	pii cur = {val[v],in[v]};

	auto it = active.upper_bound(cur);

	if(it != active.end()) {
		pii temp = *it;
		if(temp.fi == val[v])
			kanan = temp.se;
	}
	it--;
	if(it != active.begin()) {
		it--;
		pii temp = *it;
		if(temp.fi == val[v])
			kiri = temp.se;
	}

	active.erase(cur);

	int now = 0;
	if(kiri != -1) {
		kiri = inve[kiri];
		now = getLCA(v,kiri);
	}
	if(kanan != n+1) {
		kanan = inve[kanan];
		int lca = getLCA(v,kanan);
		if(depth[lca] > depth[now])
			now = lca;
	}

	update(in[v],-val[v]);
	update(in[now],val[v]);
}

void updatePath(int v) {
	if(!toggled[v]) addPath(v);
	else removePath(v);
	toggled[v] = !toggled[v];
}

void solve() {
	for(int i = 1 ; i <= q ; i++) {
		int opt, v;
		scanf("%d %d",&opt,&v);
		if(opt == 1) {
			updatePath(v);
		}
		else {
			long long ret = query(ot[v]) - query(in[v] - 1);
			assert(ret >= 0);
			printf("%lld\n",ret);
		}
	}
}

void reset() {
	active.clear();
	cnt = 0;
	for(int i = 1 ; i <= n ; i++) {
		BIT[i] = 0;
		chld[i].clear();
		toggled[i] = 0;
	}
}

int main() {
	depth[0] = -1;
	int t = 1; 
	scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		init();
		solve();
		reset();
	}
	return 0;
}