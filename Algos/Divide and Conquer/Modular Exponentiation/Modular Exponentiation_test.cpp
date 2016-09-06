// UVa - MODEX
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL recursiveModularExponentiation(LL base,LL po,LL mod) {
	if(po == 0) return 1 % mod;
	if(po % 2 == 1) return base * recursiveModularExponentiation(base,po-1,mod) % mod;
	LL temp = recursiveModularExponentiation(base,po / 2,mod);
	return temp * temp % mod;
}

LL iterativeModularExponentiation(LL base,LL po,LL mod) {
	LL ret = 1 % mod;
	while(po > 0) {
		if(po % 2 == 1) ret = ret * base % mod;
		base = base * base % mod;
		po >>= 1;
	}
	return ret;
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		int x, y, n;
		scanf("%d %d %d",&x,&y,&n);
		LL res;
		res = recursiveModularExponentiation(x,y,n);
		//res = iterativeModularExponentiation(x,y,n);
		printf("%lld\n",res);
	}
	return 0;
}