// SPOJ - MST
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 1e5 + 5;

struct edge {
	int u;
	int v;
	int cost;

	bool operator <(edge other) const {
		return cost < other.cost;
	}
};

int pset[N];
vector<edge> arr;
int n, m;

void init() {
	memset(pset,-1,sizeof pset);
}

int finds(int x) {
	return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

bool same(int u,int v) {
	return finds(u) == finds(v);
}

void join(int u,int v) {
	if(same(u,v)) return;
	u = finds(u);
	v = finds(v);
	pset[u] += pset[v];
	pset[v] = u;
}

long long kruskal() {
	init();
	sort(arr.begin(),arr.end());

	long long ans = 0;
	for(edge x : arr) {
		int u = x.u;
		int v = x.v;

		if(!same(u,v)) {
			join(u,v);
			ans += x.cost;
		}
	}

	return ans;
}

void read() {
	scanf("%d %d",&n,&m);
	for(int i = 0 ; i < m ; i++) {
		int u, v, c;
		scanf("%d %d %d",&u,&v,&c);
		arr.push_back((edge){u,v,c});
	}
}

int main() {
	read();
	printf("%lld\n",kruskal());
	return 0;
}