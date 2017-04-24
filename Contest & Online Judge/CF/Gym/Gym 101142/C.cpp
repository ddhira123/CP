#include <bits/stdc++.h>
using namespace std;

void OPEN(string name) {
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

void CLOSE() {
	fclose(stdin);
}

const int N = 1e5 + 5;
const int MX = 1e6 + 6;

pair<int,int> a[N], b[N];
int vala[N], valb[N];
int oria[N], orib[N];
int besta[N], bestb[N];
int idx[N];
int num[N], low[N];
int vis[N];
int haha;
int component;
int n;
int ans[N];

vector<int> adj[N];
vector<int> ADJ[N];
vector<int> stek;

pair<pair<int,int>,int> order[N];

int BIT[MX];
int dpa[N], dpb[N];

void update(int x) {
	for(; x < MX ; x += x & -x)
		BIT[x]++;
}

int query(int x) {
	int ret = 0 ;
	while(x) {
		ret += BIT[x];
		x -= x & -x;
	}
	return ret;
}

void tarjan(int now) {
	num[now] = low[now] = haha++;
	vis[now] = 1;
	stek.push_back(now);
	for(int nex : adj[now]) {
		if(vis[nex] == 0) tarjan(nex);
		if(vis[nex] == 1) low[now] = min(low[now], low[nex]);
	}

	if(low[now] == num[now]) {
		component++;
		while(1) {
			int cur = stek.back();
			stek.pop_back();
			vis[cur] = 2;
			besta[component] = max(besta[component], vala[cur]);
			bestb[component] = max(bestb[component], valb[cur]);
			idx[cur] = component;
			//printf("%d comp %d %d %d\n",cur,component,besta[component], bestb[component]);

			if(cur == now) {
				break;
			}
		}
	}
}

void makeGraph() {
	sort(a + 1,a + n + 1);
	sort(b + 1,b + n  + 1);

	for(int i = 2 ; i <= n ; i++) {
		adj[a[i].second].push_back(a[i-1].second);
		adj[b[i].second].push_back(b[i-1].second);
	}
}

void compressGraph() {
	for(int i = 1 ; i <= n ; i++)
		if(vis[i] == 0)
			tarjan(i);
	for(int i = 1 ; i <= n ; i++)
		for(int nex : adj[i])
			if(idx[i] != idx[nex]) {
				//printf("%d -> %d\n",idx[i],idx[nex]);
				ADJ[idx[i]].push_back(idx[nex]);
			}

	for(int i = 1 ; i <= component ; i++) {
		sort(ADJ[i].begin(), ADJ[i].end());
		ADJ[i].erase(unique(ADJ[i].begin(), ADJ[i].end()), ADJ[i].end());
		dpa[i] = -1;
		dpb[i] = -1;
	}				
}

int solvea(int x) {
	int &ret = dpa[x];
	if(ret != -1) return ret;
	ret = besta[x];
	for(int nex : ADJ[x])
		ret = max(ret,solvea(nex));
	return ret;
}

int solveb(int x) {
	int &ret = dpb[x];
	if(ret != -1) return ret;
	ret = bestb[x];
	for(int nex : ADJ[x])
		ret = max(ret,solveb(nex));
	return ret;
}

void read() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++) {
		scanf("%d %d",&vala[i],&valb[i]);
		a[i] = {vala[i], i};
		b[i] = {valb[i], i};
		orib[i] = valb[i];
	}
}

int getA(int x) {
	return lower_bound(vala + 1,vala + n + 1,x) - vala;
}

int getB(int x) {
	return lower_bound(valb + 1,valb + n + 1,x) - valb;
}

void solve() {
	makeGraph();
	compressGraph();
	for(int i = 1 ; i <= n ; i++) {
		order[i] = {{solvea(idx[i]),solveb(idx[i])},i};
		//printf("%d <%d,%d>\n",i,order[i].first.first,order[i].first.second);
	}

	sort(order + 1,order + n + 1);
	sort(vala + 1, vala + n + 1);
	sort(valb + 1,valb + n + 1);

	int iter = 1;
	for(int i = 1 ; i <= n ; i++) {
		int now = order[i].second;
		int aa = order[i].first.first;
		int bb = order[i].first.second;

		while(iter <= n && aa >= a[iter].first) {
			update(orib[a[iter].second]);
			iter++;
		}

		ans[now] = getA(aa) + getB(bb) - query(bb) - 1;
		//printf("now %d aa %d getA %d bb %d getB %d\n",now,aa,getA(aa),bb,getB(bb));
	}

	for(int i = 1 ; i <= n ; i++)
		printf("%d\n",ans[i]);
}

int main() {
	OPEN("codecoder");
	read();
	solve();
	CLOSE();
	return 0;
}