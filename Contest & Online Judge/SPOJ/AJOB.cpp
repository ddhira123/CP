#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL modPow(LL base,LL po,LL mod) {
	LL ret = 1;
	while(po) {
		if(po & 1) ret = (ret * base) % mod;
		base = (base * base) % mod;
		po >>= 1;
	}
	return ret;
}
 
LL getFactorial(LL n,LL mod) {
	LL ret = 1;
	for(LL i = 1 ; i <= n ; i++) {
		ret = (ret * i) % mod;
	}
	return ret;
}
 
LL getInverse(LL n,LL mod) {
	return modPow(getFactorial(n,mod),mod - 2,mod);
}
 
LL getCombination(LL n,LL k,LL mod) {
	if(k > n) return 0;
	LL ret = getFactorial(n,mod);
	ret = (ret * getInverse(k,mod)) % mod;
	ret = (ret * getInverse(n-k,mod)) % mod;
	return ret;
}
 
LL lucasCombination(LL n,LL k,LL mod) {
	LL ret = 1;
	while(n > 0 || k > 0) {
		ret = (ret * getCombination(n % mod,k % mod,mod)) % mod;
		n /= mod;
		k /= mod;
	}
	return ret;
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		LL n,k,mod;
		scanf("%lld %lld %lld",&n,&k,&mod);
		printf("%lld\n",lucasCombination(n+1,k+1,mod));
	}
	return 0;
}