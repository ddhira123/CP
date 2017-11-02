#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXX = 1e5 + 5;
const int N = 1e5 + 5;

int modPow(int base, int po, int mod) {
	base %= mod;
	int ret = 1 % mod;

	while(po) {
		if(po & 1) {
			ret = 1ll * ret * base % mod;
		}

		base = 1ll * base * base % mod;
		po >>= 1;
	}

	return ret;
}

int arr[N];
int cnt[MAXX];
int ways[MAXX];
int n, k;

void read() {
	scanf("%d %d", &n, &k);
	for(int i = 0 ; i < n ; i++) {
		scanf("%d", arr + i);
	}
}

int solve() {
	// init cnt
	for(int i = 0 ; i < n ; i++) {
		cnt[arr[i]]++;
	}

	// make cnt[i] contains number of elements in array
	// which is a multiple of i
	for(int i = 1 ; i < MAXX ; i++)
		for(int j = i + i ; j < MAXX ; j += i)
			cnt[i] += cnt[j];

	// make k equal to 2^k % (MOD-1)
	k = modPow(2, k, MOD-1);

	for(int i = MAXX-1 ; i >= 1 ; i--) {
		// initially, there are cnt[i]^(2^k) combination
		// whose gcd is multiple of i
		// according to fermat's little theorem
		// 2^k can be reduced to 2^k % (MOD-1)
		ways[i] = modPow(cnt[i], k, MOD);

		// make ways[i] equal to number of combination
		// whose gcd is exactly i
		for(int j = i + i ; j < MAXX ; j += i) {
			ways[i] = (ways[i] - ways[j] + MOD) % MOD;
		}
	}

	// now, calculate the sum
	int ret = 0;
	for(int i = 1 ; i < MAXX ; i ++) {
		ret = (ret + 1ll * ways[i] * i) % MOD;
	}

	return ret;
}

int main() {
	read();
	printf("%d\n", solve());
	return 0;
}
