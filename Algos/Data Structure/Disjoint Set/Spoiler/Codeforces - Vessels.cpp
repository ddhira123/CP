#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int pset[N];
int cap[N];
int sum[N];
int n, m;

int finds(int x) {
	return pset[x] == x ? x : pset[x] = finds(pset[x]);
}

void join(int x,int y) {
	pset[finds(x)] = finds(y);
}

void init() {
	for(int i = 0 ; i < N ; i++)
		pset[i] = i;
}

void update(int x,int k) {
	x = finds(x);
	while(x <= n && k > 0) {
		int add = min(cap[x] - sum[x],k);
		sum[x] += add;
		k -= add;
		if(sum[x] == cap[x]) join(x,x+1);
		x = finds(x);
	}
}

int main() {
	init();
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",cap + i);
	scanf("%d",&m);
	for(int i = 0 ; i < m ; i++) {
		int opt; scanf("%d",&opt);
		if(opt == 2) {
			int x; scanf("%d",&x);
			printf("%d\n",sum[x]);
		}
		else {
			int x, k;
			scanf("%d %d",&x,&k);
			update(x,k);
		}
	}
	return 0;
}