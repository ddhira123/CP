#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 5;
const int LOG = 17;

typedef pair<int,int> pii;
#define fi first
#define se second

pii anc[N][LOG];
vector<pii> adj[N];
int depth[N];
int pset[N];
int score[N];

pair<int,pii> query[N];
vector<int> update[N];
int u[N], v[N];

int n,m,q;

void init() {
	for(int i = 1 ; i <= n ; i++) {
		pset[i] = i;
		score[i] = 0;
	}
}

int finds(int x) {
	return pset[x] == x ? x : pset[x] = finds(pset[x]);
}

bool join(int x,int y) {
	x = finds(x); y = finds(y);
	if(x == y) return 0;
	pset[x] = y;
	score[y] += score[x];
	return 1;
}

void build(int prv,int now,int cost) {
	depth[now] = depth[prv] + 1;
	anc[now][0] = {prv,cost};

	for(int i = 1 ; (1<<i) <= depth[now] ; i++) {
		pii papa = anc[now][i-1];
		pii grandpa = anc[papa.fi][i-1];
		anc[now][i] = {grandpa.fi,max(papa.se,grandpa.se)};
	}
}

void dfs(int now,int prv) {
	for(pii nex : adj[now]) {
		if(nex.fi == prv) continue;
		build(now,nex.fi,nex.se);
		dfs(nex.fi,now);
	}
}

pii getLCA(int a,int b) {
	if(depth[a] > depth[b]) swap(a,b);
	pii ans = {-1,0};

	int diff = depth[b] - depth[a];
	for(int i = 0 ; diff > 0 ; i++)
		if(diff & (1<<i)) {
			diff ^= (1 << i);
			ans.se = max(ans.se,anc[b][i].se);
			b = anc[b][i].fi;
		}

	if(a == b) {
		ans.fi = a;
		return ans;
	}	

	for(int i = LOG - 1 ; i >= 0 ; i--)
		if(depth[a] >= (1<<i) && anc[a][i].fi != anc[b][i].fi) {
			ans.se = max(ans.se,max(anc[a][i].se,anc[b][i].se));
			a = anc[a][i].fi;
			b = anc[b][i].fi;
		}

	ans.se = max(ans.se,max(anc[a][0].se,anc[b][0].se));
	ans.fi = anc[a][0].fi;

	return ans;	
}

void makeTree() {
	for(int i = 0 ; i < q ; i++)
		if(query[i].fi == 1 && join(query[i].se.fi,query[i].se.se)) {
			int a = query[i].se.fi;
			int b = query[i].se.se;
			adj[a].push_back({b,i});
			adj[b].push_back({a,i});
		}

	for(int i = 1 ; i <= n ; i++)
		if(finds(i) == i)
			dfs(i,-1);	
}

void makeUpdate() {
	for(int i = 0 ; i < m ; i++)
		if(finds(u[i]) == finds(v[i])) {
			int t = getLCA(u[i],v[i]).se;
			update[t].push_back(u[i]);
		}
}

void read() {
	scanf("%d %d %d",&n,&m,&q);
	for(int i = 0 ; i < m ; i++)
		scanf("%d %d",u + i,v + i);
	for(int i = 0 ; i < q ; i++) {
		scanf("%d %d",&query[i].fi,&query[i].se.fi);
		if(query[i].fi == 1) scanf("%d",&query[i].se.se);
	}
}

void prepare() {
	init();
	makeTree();
	makeUpdate();
}

void solve() {
	init();
	for(int i = 0 ; i < q ; i++) {
		if(query[i].fi == 1) {
			join(query[i].se.fi,query[i].se.se);
			for(int x : update[i])
				score[finds(x)]++;
		}
		else {
			printf("%d\n",score[finds(query[i].se.fi)]);
		}
	}
}

void reset() {
	for(int i = 0 ; i <= n ; i++) {
		adj[i].clear();
		depth[i] = 0;
	}
	for(int i = 0 ; i <= q ; i++)
		update[i].clear();
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		prepare();
		solve();
		reset();
	}
	return 0;
}