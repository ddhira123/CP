// UVa - 10608
#include <bits/stdc++.h>
using namespace std;

const int N = 3e4 + 5;

int pset[N];
int n, m;

void init(int x) {
	for(int i = 0 ; i <= x ; i++)
		pset[i] = -1;
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

int solve() {
	scanf("%d %d",&n,&m);
	init(n);

	for(int i = 0 ; i < m ; i++) {
		int u, v;
		scanf("%d %d",&u,&v);
		join(u,v);
	}

	int maks = 0;
	for(int i = 1 ; i <= n ; i++)
		maks = max(maks,-pset[finds(i)]);

	return maks;
}

int main() {
	int t; scanf("%d",&t);

	for(int tc = 1 ; tc <= t ; tc++)
		printf("%d\n",solve());
	return 0;
}