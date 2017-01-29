#include <bits/stdc++.h>
using namespace std;

long long n;
int k;

long long get(int x,int po) {
	long long ret = 1;
	for(int i = 1 ; i <= po ; i++) {
		if(n / x >= ret) {
			ret *= x;
		} else {
			return -1;
		}
	}
	return ret;
}

long long val[1000005];

int main() {
	cin >> n >> k;
	if(k == 1) {
		n *= 2;
		for(long long i = 2 ; i * i <= n ; i++)
			if(n % i == 0) {
				long long len = i;
				long long haha = n / len;
				long long lol = haha + 1 - len;
				if(lol % 2 == 0) {
					lol /= 2;
					printf("%lld %lld\n", lol, lol + len-1);
					return 0;
				}
			}
		puts("-1");
		return 0;
	}
	val[1] = 1;
	int l = 1;
	long long sum = 1;
	for(int i = 2 ; ; i++) {
		val[i] = get(i, k);
		if(val[i] == -1) {
			puts("-1");
			return 0;
		} 
		sum += val[i];
		while(sum > n) {
			sum -= val[l++];
		}

		if(sum == n && l != i) {
			printf("%d %d\n", l, i);
			return 0;
		}
	}
	return 0;
}