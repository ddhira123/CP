#include <bits/stdc++.h>
using namespace std;

void OPEN(string name) {
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

void CLOSE() {
	fclose(stdin);
}

const int N = 100005;
const int LOG = 18;

int depth[N];
int anc[N][LOG];
int in[N], ot[N], inve[N];
int cnt;
int leaf[N];
vector<int> chld[N];
int occ[N];
int highest[N];
set<int> asu[N];
int total;
int cut;
int active;
int n, q;

int getHigher(int a,int b) {
	return depth[a] < depth[b] ? a : b;
}

void make(int now,int prv) {
	depth[now] = depth[prv]+1;
	anc[now][0] = prv;
	for(int i = 1 ; (1<<i) <= depth[now] ; i++)
		anc[now][i] = anc[anc[now][i-1]][i-1];
}

void dfs(int now) {
	in[now] = ++cnt;
	inve[cnt] = now;
	leaf[now] = chld[now].empty();
	for(int nex : chld[now]) {
		make(nex,now);
		dfs(nex);
		leaf[now] += leaf[nex];
	}
	ot[now] = cnt;
}

int getKth(int now,int kth) {
	for(int i = 0 ; kth ; i++)
		if(kth & (1<<i)) {
			now = anc[now][i];
			kth ^= (1<<i);
		}
	return now;	
}

int getLCA(int u,int v) {
	if(depth[u] < depth[v]) swap(u,v);
	for(int i = 0 ; depth[u] != depth[v] ; i++)
		if((depth[u] - depth[v]) & (1<<i))
			u = anc[u][i];

	if(u == v) return u;
	for(int i = LOG-1 ; i >= 0 ; i--)
		if(depth[u] >= (1<<i) && anc[u][i] != anc[v][i]) {
			u = anc[u][i];
			v = anc[v][i];
		}	

	return anc[u][0];
}

void build() {
	dfs(1);
	//printf("dfs done\n");
	for(int i = 2 ; i <= n ; i++)
		highest[i] = getKth(i,depth[i]-1);
	//puts("build done");
}

int getMins(int x) {
	return *(asu[x].begin());
}

int getMaks(int x) {
	auto it = asu[x].end();
	it--;
	return *it;
}

void adder(int x) {
	active++;
	int papa = highest[x];
	if(occ[papa] == 0) {
		total++;
		cut++;
		asu[papa].insert(in[x]);
		occ[papa]++;
	}
	else {
		int prv = getLCA(inve[getMins(papa)], inve[getMaks(papa)]);
		cut -= leaf[prv];

		occ[papa]++;
		asu[papa].insert(in[x]);
		int cur = getLCA(inve[getMins(papa)], inve[getMaks(papa)]);
		cut += leaf[cur];
	}
}

void remover(int x) {
	int papa = highest[x];
	if(occ[papa] == 1) {
		total--;
		cut--;
		asu[papa].erase(in[x]);
		occ[papa]--;
	}
	else {
		int prv = getLCA(inve[getMins(papa)], inve[getMaks(papa)]);
		cut -= leaf[prv];

		occ[papa]--;
		asu[papa].erase(in[x]);
		int cur = getLCA(inve[getMins(papa)], inve[getMaks(papa)]);
		cut += leaf[cur];
	}
	active--;
}

void read() {
	scanf("%d %d",&n,&q);
	for(int i = 2 ; i <= n ; i++) {
		int x; scanf("%d",&x);
		chld[x].push_back(i);
	}
}

void solve() {
	build();
	for(int i = 0 ; i < q;  i++) {
		char s[5];
		int x;
		scanf("%s %d",s,&x);
		if(s[0] == '+') adder(x);
		else remover(x);
		printf("%d %d\n",total,cut - active);
	}
}

int main() {
	OPEN("gangsters");
	read();
	solve();
	CLOSE();
	return 0;
}