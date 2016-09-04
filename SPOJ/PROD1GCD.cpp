#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MX = 1e7 + 5;
const int PRIMES = 7e5;
typedef long long LL;

bool flag[MX];
int prime[PRIMES];
int cnt;
LL n, m;

void sieve() {
	for(int i = 2 ; i < MX ; i++)
		if(!flag[i]) {
			prime[cnt++] = i;
			for(int j = i ; j < MX / i ; j++)
				flag[i*j] = 1;
		}	
}

LL modPow(LL base,LL po) {
	LL ret = 1;
	while(po) {
		if (po & 1) ret = (ret * base) % MOD;
		base = (base * base) % MOD;
		po >>= 1;
	}
	return ret;
}

LL solve() {
	LL ret = 1;
	int mins = min(n,m);
	for(int i = 0 ; i < cnt && prime[i] <= mins ; i++) {
		int x = n;
		int y = m;

		long long add = 0;
		while(x > 0 && y > 0) {
			x /= prime[i];
			y /= prime[i];
			add += 1ll * x * y;
		}

		ret = (ret * modPow(prime[i],add)) % MOD;
	}
	return ret;
}

int main() {
	sieve();
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		cin >> n >> m;
		//assert(1 <= n && n <= 1e7);
		//assert(1 <= m && m <= 1e7);
		cout << solve() << "\n";
	}
	return 0;
}