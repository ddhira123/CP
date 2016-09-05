// WA
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 2e5 + 5;
const int LOG = 18;

#define fi first
#define se second

struct node {
	LL maks;
	LL lazy;

	node() {
		maks = lazy = 0;
	}

	node operator +(node other) const {
		node res;
		res.lazy = 0;
		res.maks = max(maks+lazy,other.maks+other.lazy);
		return res;
	}
};

int anc[N][LOG];
LL path[N][LOG];
int depth[N];

int cnt;
int in[N], ot[N];
int inve[N];

vector<pair<int,LL>> spec[N];
vector<pair<pair<int,int>,LL>> event[N];

vector<pair<int,LL>> adj[N];
int n, M;

LL ans;

node stree[4*N];

void build(int prv,int now,LL cost) {
	anc[now][0] = prv;
	path[now][0] = cost;
	depth[now] = depth[prv]+1;
	for(int i = 1 ; (1<<i) <= depth[now] ; i++) {
		int papa = anc[now][i-1];
		anc[now][i] = anc[papa][i-1];
		path[now][i] = path[now][i-1] + path[papa][i-1];
	}
}

// is b descendant of a?
bool isDescendant(int a,int b) {
	return in[a] <= in[b] && in[b] <= ot[a];
}

void dfs(int now,int prv) {
	in[now] = ++cnt;
	inve[cnt] = now;
	for(pair<int,LL> nex : adj[now]) {
		if(nex.fi == prv) continue;
		build(now,nex.fi,nex.se);
		dfs(nex.fi,now);
	}
	ot[now] = cnt;
}

pair<int,LL> getLCA(int u,int v) {
	if(depth[u] < depth[v]) swap(u,v);
	int diff = depth[u] - depth[v];
	LL tot = 0;

	for(int i = 0 ; diff ; i++)
		if(diff & (1<<i)) {
			tot += path[u][i];
			u = anc[u][i];
			diff ^= (1<<i);
		}

	if(u == v) return {u,tot};

	for(int i = LOG-1; i >= 0 ; i--)
		if(depth[u] >= (1<<i) && anc[u][i] != anc[v][i]) {
			tot += path[u][i] + path[v][i];
			u = anc[u][i];
			v = anc[v][i];
		}	

	tot += path[u][0] + path[v][0];
	u = anc[u][0];
	return {u,tot};	
}

int getKth(int x,int k) {
	for(int i = 0 ; k ; i++)
		if(k & (1<<i)) {
			k ^= (1<<i);
			x = anc[x][i];
		}
	return x;	
}

void buildS(int id,int l,int r) {
	stree[id].lazy = 0;
	if(l == r) {
		stree[id].maks = -getLCA(1,inve[l]).se;
	}
	else {
		int m = (l + r) / 2;
		int chld = id << 1;

		buildS(chld,l,m);
		buildS(chld+1,m+1,r);

		stree[id] = stree[chld] + stree[chld+1];
	}
}

void propagate(int id) {
	int chld = id << 1;
	for(int i = 0 ; i < 2 ; i++)
		stree[chld+i].lazy += stree[id].lazy;
	stree[id].lazy = 0;
}

void updateS(int id,int l,int r,int x,int y,LL val) {
	if(x <= l && r <= y)
		stree[id].lazy += val;
	else {
		int m = (l + r) / 2;
		int chld = id << 1;
		propagate(id);

		if(x <= m) updateS(chld,l,m,x,y,val);
		if(y > m)  updateS(chld+1,m+1,r,x,y,val);

		stree[id] = stree[chld] + stree[chld+1];
	}
}

LL query(int id,int l,int r,int x,int y) {
	if(x <= l && r <= y)
		return stree[id].maks+stree[id].lazy;
	else {
		int m = (l+r) / 2;
		int chld = id << 1;
		LL ret = -4e18;
		propagate(id);

		if(x <= m) ret = max(ret,query(chld,l,m,x,y));
		if(y > m)  ret = max(ret,query(chld+1,m+1,r,x,y));

		stree[id] = stree[chld] + stree[chld+1];
		return ret;
	}
}

LL getValue(int a,int b) {
	/*if(a == b) {
		LL ret = query(1,1,n,in[a],ot[a]);
		ret += getLCA(1,a).se;
		return ret;
	}*/
	if(in[a] > in[b]) swap(a,b);

	int lca = getLCA(a,b).fi;
	LL ret = 2 * getLCA(1,lca).se;
	ret += query(1,1,n,in[b],ot[b]);
	if(!isDescendant(a,b)) 
		ret += query(1,1,n,in[a],ot[a]);
	else  {
		/*LL add = query(1,1,n,in[a],ot[a]);
		int atas = getKth(b,depth[b]-depth[a]-1);
		int kiri = in[atas]-1;
		int kanan = ot[atas]+1;

		if(in[a] <= kiri) add = max(add,query(1,1,n,in[a],kiri));
		if(kanan <= ot[a]) add = max(add,query(1,1,n,kanan,ot[a]));
		ret += add;*/
		ret -= getLCA(1,lca).se;
	}
	//cerr << "hasil " << a << " " << b << " " << ret << endl;
	return ret;
}

bool cmp(pair<pair<int,int>,LL> a,pair<pair<int,int>,LL> b) {
	if(in[a.fi.fi] == in[b.fi.fi]) 
		return in[a.fi.se] < in[b.fi.se];
	return in[a.fi.fi] < in[b.fi.fi];
}

void solve(int now,int prv) {
	for(pair<int,LL> nex : adj[now]) {
		if(nex.fi == prv) continue;
		solve(nex.fi,now);
	}
	
	for(pair<int,LL> special : spec[now]) {
		int idx = special.fi;
		LL val = special.se;

		updateS(1,1,n,in[idx],ot[idx],val);
	}

	for(pair<int,LL> special : spec[now]) {
		ans = max(ans,getValue(special.fi,now));
	}

	sort(event[now].begin(),event[now].end(),cmp);
	vector<pair<pair<int,int>,LL>> stek;

	for(pair<pair<int,int>,LL> ev : event[now]) {
		while(!stek.empty() && !isDescendant(stek.back().fi.fi,ev.fi.fi)) {
			LL val = stek.back().se;

			int idx = stek.back().fi.se;
			//update(in[idx],-val);
			//update(ot[idx]+1,val);
			updateS(1,1,n,in[idx],ot[idx],-val);

			stek.pop_back();
		}

		stek.push_back(ev);

		int idx = stek.back().fi.se;
		LL val = stek.back().se;
		//update(in[idx],val);
		//update(ot[idx]+1,-val);
		updateS(1,1,n,in[idx],ot[idx],val);
		ans = max(ans,getValue(stek.back().fi.fi,idx));		
	}

	while(!stek.empty()) {
		LL val = stek.back().se;

		int idx = stek.back().fi.se;
		//update(in[idx],-val);
		//update(ot[idx]+1,val);
		updateS(1,1,n,in[idx],ot[idx],-val);

		stek.pop_back();
	}
}

void init() {
	scanf("%d",&n);
	for(int i = 1 ; i < n ; i++) {
		int u, v, c;
		scanf("%d %d %d",&u,&v,&c);
		adj[u].push_back({v,c});
		adj[v].push_back({u,c});
	}

	dfs(1,-1);
	buildS(1,1,n);

	scanf("%d",&M);
	for(int i = 0 ; i < M ; i++) {
		int u, v, c;
		scanf("%d %d %d",&u,&v,&c);

		if(in[u] > in[v]) swap(u,v);
		if(isDescendant(u,v))
			spec[u].push_back({v,c});
		else {
			int lca = getLCA(u,v).fi;
			event[lca].push_back({{u,v},c});
		}
	}
}

void work() {
	ans = 0;
	solve(1,-1);
	printf("%lld\n",ans);
}

int main() {
	init();
	work();
	return 0;
}