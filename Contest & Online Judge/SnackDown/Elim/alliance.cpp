#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 500005;
const int LOG = 20;

int anc[N][LOG];
int depth[N];
vector<int> adj[N];
vector<int> gang[N];
int in[N], ot[N], cnt;
int inve[N];
int n, k, q;
int iter[N];
int sebelum[N];
vector<int> stek;

int inRange(int lo,int x,int hi) {
	return lo <= x && x <= hi;
}

void build(int now,int prv) {
	depth[now] = depth[prv] + 1;
	anc[now][0] = prv;

	for(int i = 1 ; (1 << i) <= depth[now] ; i++) {
		int papa = anc[now][i-1];
		anc[now][i] = anc[papa][i-1];
	}
}

void dfs(int haha,int prv) {
	memset(iter,-1,sizeof iter);
	for(int i = 1 ; i <= n ; i++) sebelum[i] = -1;
	sebelum[1] = 0;
	stek.push_back(1);
	while(!stek.empty()) {
		int now = stek.back();
		//cerr << now << endl;
		if(iter[now] == -1) {
			in[now] = ++cnt;
			inve[cnt] = now;
			iter[now] = 0;
		}
		for(; iter[now] < adj[now].size() ; iter[now]++) {
			int x = adj[now][iter[now]];
			if(sebelum[x] != -1) continue;
			sebelum[x] = now;
			build(x,now);
			stek.push_back(x);
			break;
		}
		if(iter[now] == adj[now].size()) {
			ot[now] = cnt;
			stek.pop_back();
		}
	}
}

int LCA(int u,int v) {
	if(depth[u] < depth[v]) swap(u,v);
	int diff = depth[u] - depth[v];
	for(int i = 0 ; diff > 0 ; i++)
		if(diff & (1<<i)) {
			diff ^= (1<<i);
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

int getDist(int u,int v) {
	int lca = LCA(u,v);
	return depth[u] + depth[v] - 2*depth[lca];
}

pair<int,int> get(int x,int id) {
	//printf("id %d\n",id);
	auto it = upper_bound(gang[id].begin(),gang[id].end(),x);
	pair<int,int> ret = {-1,-1};
	if(it != gang[id].end()) ret.second = *it;
	if(it != gang[id].begin()) {
		it--;
		ret.first = *it;
	}
	//printf("%d %d\n",ret.fi,ret.se);
	return ret;
}

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i < n ; i++) {
		int u, v;
		scanf("%d %d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
}

void make() {
	dfs(1,0);

	scanf("%d",&k);
	for(int i = 1 ; i <= k ; i++) {
		int sz; scanf("%d",&sz);
		for(int j = 0 ; j < sz ; j++) {
			int x; scanf("%d",&x);
			gang[i].push_back(in[x]);
		}
		sort(gang[i].begin(),gang[i].end());
	}

	//puts("done");
}

int solve(int x,vector<int> &active) {
	pair<int,int> byIn = {-1,n+1};
	for(int it : active) {
		pair<int,int> temp = get(in[x],it);
		if(temp.first != -1) byIn.fi = max(byIn.fi,temp.fi);
		if(temp.second != -1) byIn.se = min(byIn.se,temp.se);
	}
	//puts("ye");
	if(byIn.fi == in[x]) return 0;

	if(byIn.fi != -1 && byIn.se != n+1 && !inRange(in[x],byIn.fi,ot[x]) && inRange(in[x],byIn.se,ot[x])) 
		return 0;

	pii byOt = {-1,n+1};
	for(int it : active) {
		pii temp = get(ot[x],it);
		if(temp.fi != -1) byOt.fi = max(byOt.fi,temp.fi);
		if(temp.se != -1) byOt.se = min(byOt.se,temp.se);
	}
	if(byOt.fi != -1 && byOt.se != n+1 && inRange(in[x],byOt.fi,ot[x]) && !inRange(in[x],byOt.se,ot[x]))
		return 0;
	//puts("yo");
	// dalam semua
	//printf("%d %d %d %d\n",byIn.fi,byIn.se,byOt.fi,byOt.se);
	if(byIn.fi == -1 && byOt.se == n+1) {
		int mins = n+1;
		int maks = -1;
		for(int it : active) {
			mins = min(mins,gang[it][0]);
			maks = max(maks,gang[it].back());
		}
		mins = inve[mins];
		maks = inve[maks];
		int lca = LCA(mins,maks);
		return getDist(lca,x);
	}

	// kiri kanan ada
	if(byIn.fi != -1 && byOt.se != n+1) {
		//puts("asu");
		int ret = n + 5;
		int kiri = byIn.fi;
		int kanan = byOt.se;

		kiri = inve[kiri];
		kanan = inve[kanan];

		ret = getDist(x,LCA(x,kiri));
		ret = min(ret,getDist(x,LCA(x,kanan)));

		return ret;
	}

	//puts("sini cok");
	// kiri semua atau kanan semua
	int mins = n+1;
	int maks = -1;
	for(int it : active) {
		mins = min(mins,gang[it][0]);
		maks = max(maks,gang[it].back());
	}
	mins = inve[mins];
	maks = inve[maks];
	int lca = LCA(mins,maks);
	int lcax = byIn.fi != -1 ? LCA(x,maks) : LCA(x,mins);

	if(inRange(in[lca],in[lcax],ot[lca])) return getDist(lcax,x);
	return getDist(x,lca);
}

void work() {
	scanf("%d",&q);
	for(int i = 0 ; i < q ; i++) {
		int x; scanf("%d",&x);
		int sz; scanf("%d",&sz);

		vector<int> active;
		for(int j = 0 ; j < sz ; j++) {
			int v; scanf("%d",&v);
			active.push_back(v);
		}

		printf("%d\n",solve(x,active));
	}
}

int main() {
	read();
	make();
	work();
	return 0;
}