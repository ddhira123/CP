#include <bits/stdc++.h>
using namespace std;

long long getOdd(long long n) {
	if(n == 0) return 1;
	long long ret = 1;
	while(n > 0) {
		ret *= ((n % 2) + 1);
		n /= 2;
	}
	return ret;
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		long long n; scanf("%lld",&n);
		long long odd = getOdd(n);
		long long even = n - odd + 1;

		printf("%lld %lld\n",even,odd);
	}
	return 0;
}