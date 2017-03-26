#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

map<int,int> dp;

int solve(int x) {
	if(dp.count(x)) {
		return dp[x];
	}

	int ret = 0;
	bool isPrime = 1;
	for(int i = 2 ; i*i <= x ; i++)
		if(x % i == 0) {
			isPrime = false;
			int j = x / i;
			if(i != j) {
				ret = (ret + 1ll * solve(i) * solve(j)) % MOD;
			} else {
				long long same = solve(i);
				long long diff = 1ll * same * (same-1) / 2;
				ret =  (ret + same + diff) % MOD;
			}
		}

	if(isPrime) {
		ret = 1;
	}
	return dp[x] = ret;
}

int calc(int x) {
	return solve(x);
}

int main() {
	int x;
	cin >> x;
	cout << calc(x) << "\n";
	return 0;
}