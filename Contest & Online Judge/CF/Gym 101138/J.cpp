#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 100005;
const int LOG = 17;

struct node {
	LL sum;
	LL maks;
	LL pref;
	LL suf;

	node operator +(node other) const {
		node res;
		res.sum = sum + other.sum;
		res.pref = max(pref, sum + other.pref);
		res.suf = max(other.suf, other.sum + suf);
		res.maks = max(maks, other.maks);
		res.maks = max(res.maks, suf + other.pref);

		return res;
	}
};

int anc[N][LOG];
node data[N][LOG];
int depth[N];
vector<int> adj[N];
int arr[N];
int n, q;

void build(int now,int par) {
	anc[now][0] = par;
	depth[now] = depth[par]+1;
	anc[now][0] = par;
	int collapse = arr[now];
	data[now][0] = (node){arr[now],collapse,collapse,collapse};

	for(int i = 1 ; (1<<i) <= depth[now] ; i++) {
		anc[now][i] = anc[anc[now][i-1]][i-1];
		data[now][i] = data[now][i-1] + data[anc[now][i-1]][i-1];
	}
}

void dfs(int now) {
	for(int nex : adj[now]) {
		if(nex == anc[now][0]) continue;
		build(nex,now);
		dfs(nex);
	}
}

int getLCA(int u,int v) {
	if(depth[u] < depth[v]) swap(u,v);
	int diff = depth[u] - depth[v];
	for(int i = 0 ; i < LOG ; i++)
		if(diff & (1<<i)) {
			u = anc[u][i];
		}

	if(u == v) return u;

	for(int i = LOG-1 ; i >= 0 ; i--)
		if(depth[u] >= (1<<i) && anc[u][i] != anc[v][i]) {
			u = anc[u][i];
			v = anc[v][i];
		}	

	return anc[u][0];
}

vector<node> getPath(int now, int step) {
	vector<node> res;
	for(int i = 0 ; i < LOG ; i++)
		if(step & (1<<i)) {
			res.push_back(data[now][i]);
			now = anc[now][i];
		}
	res.push_back(data[now][0]);
	
	return res;	
}

LL solve(int a,int b) {
	int lca = getLCA(a,b);
	//printf("%d %d lca %d\n",a,b,lca);
	vector<node> fw = getPath(a,depth[a]-depth[lca]);
	vector<node> bw;
	if(b != lca)
		bw = getPath(b,depth[b]-depth[lca]-1);
	for(int i = 0 ; i < bw.size() ; i++)
		swap(bw[i].suf,bw[i].pref);

	node ret = fw[0];
	for(int i = 1 ; i < fw.size() ; i++) ret = ret + fw[i];
	for(int i = (int)bw.size()-1 ; i >= 0 ; i--) ret = ret + bw[i];

	return ret.maks;
}

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i < n ; i++) {
		int u, v;
		scanf("%d %d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",arr + i);
}

void work() {
	data[1][0] = (node){arr[1],arr[1],arr[1],arr[1]};
	dfs(1);
	scanf("%d",&q);
	for(int i = 1 ; i <= q ; i++) {
		int u, v;
		scanf("%d %d",&u,&v);
		printf("%lld\n",solve(u,v));
	}
}

int main() {
	read();
	work();
	return 0;
}