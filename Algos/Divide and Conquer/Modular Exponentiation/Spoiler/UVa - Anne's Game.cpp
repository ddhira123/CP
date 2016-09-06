#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL MOD = 2000000011;

LL modPow(LL base,int po) {
	LL ret = 1;
	while(po) {
		if(po & 1) ret = (ret * base) % MOD;
		base = base * base % MOD;
		po >>= 1;
	}
	return ret;
}

LL calc(int x) {
	return x == 1 ? 1 : modPow(x,x-2);
}

int main() {
	int t; scanf("%d",&t);

	for(int tc = 1 ; tc <= t ; tc++) {
		int n; scanf("%d",&n);
		printf("Case #%d: %lld\n",tc,calc(n));
	}
	return 0;
}