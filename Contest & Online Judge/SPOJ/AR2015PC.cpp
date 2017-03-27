#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int LOG = 17;
const int M = 105;

typedef pair<int,int> pii;
#define fi first
#define se second

pii anc[N][LOG];
int depth[N];

int dist[M][M];
vector<int> uniq;
vector<pii> adj[N];

int pset[N + 5];

pair<pii,int> edge[N + M];
bool pake[N + M];

int n,m,q;

void build(int now,int prv,int dst) {
	anc[now][0] = {prv,dst};
	depth[now] = depth[prv] + 1;

	for(int i = 1 ; (1 << i) <= depth[now] ; i++) {
		pii papa = anc[now][i - 1];
		pii grandpa = anc[papa.fi][i - 1];
		anc[now][i] = {grandpa.fi,grandpa.se + papa.se};
	}
}

void dfs(int now,int prv) {
	for(pii nex : adj[now]) {
		if(nex.fi == prv) continue;
		build(nex.fi,now,nex.se);
		dfs(nex.fi,now);
	}
}

void init() {
	for(int i = 1 ; i <= n ; i++)
		pset[i] = i;
}

int finds(int x) {
	return pset[x] == x ? x : pset[x] = finds(pset[x]);
}

void join(int u,int v) {
	u = finds(u);
	v = finds(v);
	pset[v] = u;
}

pii getLCA(int u,int v) {
	pii ret = {0,0};

	if(depth[u] < depth[v]) swap(u,v);
	int diff = depth[u] - depth[v];

	for(int i = 0 ; diff > 0 ; i++)
		if(diff & (1 << i)) {
			diff ^= (1 << i);
			ret.se += anc[u][i].se;
			u = anc[u][i].fi;
		}

	if(u == v) {
		ret.fi = u;
		return ret;
	}

	for(int i = LOG - 1 ; i >= 0 ; i--)
		if(depth[u] >= (1 << i) && anc[u][i].fi != anc[v][i].fi) {
			ret.se += anc[u][i].se;
			ret.se += anc[v][i].se;
			u = anc[u][i].fi;
			v = anc[v][i].fi;
		}

	ret.se += anc[u][0].se;
	ret.se += anc[v][0].se;	
	ret.fi = anc[u][0].fi;	

	return ret;	
}

void makeUniq() {
	for(int i = 0 ; i < m ; i++)
		if(!pake[i]) {
			uniq.push_back(edge[i].fi.fi);
			uniq.push_back(edge[i].fi.se);
		}
	sort(uniq.begin(),uniq.end());
	uniq.erase(unique(uniq.begin(),uniq.end()),uniq.end());
}

int getID(int x) {
	return lower_bound(uniq.begin(),uniq.end(),x) - uniq.begin();
}

void floydWarshall() {
	for(int i = 0 ; i < uniq.size() ; i++)
		for(int j = 0 ; j < uniq.size() ; j++)
			dist[i][j] = getLCA(uniq[i],uniq[j]).se;

	for(int i = 0 ; i < m ; i++) 
		if(!pake[i]) {
			int u = edge[i].fi.fi;
			int v = edge[i].fi.se;
			int c = edge[i].se;

			u = getID(u);
			v = getID(v);

			dist[u][v] = dist[v][u] = min(dist[v][u],c);
		}

	for(int i = 0 ; i < uniq.size() ; i++)
		for(int j = 0 ; j < uniq.size() ; j++)
			for(int k = 0 ; k < uniq.size() ; k++)
				dist[j][k] = min(dist[j][k],dist[j][i] + dist[i][k]);		
}

int query(int u,int v) {
	int ret = getLCA(u,v).se;
	vector<int> disU(uniq.size() + 1);
	vector<int> disV(uniq.size() + 1);

	for(int i = 0 ; i < uniq.size() ; i++) {
		disU[i] = getLCA(u,uniq[i]).se;
		disV[i] = getLCA(v,uniq[i]).se;
	}

	for(int i = 0 ; i < uniq.size() ; i++)
		for(int j = 0 ; j < uniq.size() ; j++) {
			int a = uniq[i];
			int b = uniq[j];

			ret = min(ret,disU[i] + dist[i][j] + disV[j]);
		}

	return ret;	
}

void read() {
	scanf("%d %d %d",&n,&m,&q);
	for(int i = 0 ; i < m ; i++) {
		scanf("%d %d %d",&edge[i].fi.fi,&edge[i].fi.se,&edge[i].se);
	}
}

void make_graph() {
	for(int i = 0 ; i < m ; i++) {
		int u = edge[i].fi.fi;
		int v = edge[i].fi.se;
		int c = edge[i].se;

		if(finds(u) != finds(v)) {
			adj[u].push_back({v,c});
			adj[v].push_back({u,c});
			pake[i] = 1;
			join(u,v);
		}
	}

	makeUniq();
	dfs(1,0);
	floydWarshall();
}

void solve() {
	for(int i = 0 ; i < q ; i++) {
		int u,v;
		scanf("%d %d",&u,&v);
		printf("%d\n",query(u,v));
	}
}

void reset() {
	uniq.clear();
	for(int i = 1 ; i <= n ; i++)
		adj[i].clear();
	for(int i = 0 ; i < m ; i++)
		pake[i] = 0;
}

int main() {
	int t; //t = 1;
	scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		printf("Case %d:\n",tc);
		init();
		make_graph();
		solve();
		reset();
	}
	return 0;
}