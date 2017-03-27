#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 1000005;
const LL MOD = 999999937;

int pset[N];
int n,m;

LL modPow(LL base,int po) {
	LL ret = 1;
	while(po) {
		if(po & 1) ret = (ret * base) % MOD;
		base = (base * base) % MOD;
		po >>= 1;
	}
	return ret;
}

void reset() {
	for(int i = 1 ; i <= n ; i++)
		pset[i] = -1;
}

int finds(int x) {
	return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

void join(int u,int v) {
	u = finds(u);
	v = finds(v);
	if(u == v) return;
	pset[u] += pset[v];
	pset[v] = u;
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%d %d",&n,&m);
		reset();
		for(int i = 1 ; i <= m ; i++) {
			int u,v; scanf("%d %d",&u,&v);
			join(u,v);
		}
		LL ans = 1;
		int component = 0;
		for(int i = 1 ; i <= n ; i++)
			if(finds(i) == i) {
				component++;
				ans = (ans * (-pset[i])) % MOD;
			}
		if(component == 1)
			ans = 1;
		else
			ans = (ans * modPow(n,component - 2)) % MOD;
		printf("%lld\n",ans);			
	}
	return 0;
}