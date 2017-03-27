#include <bits/stdc++.h>
using namespace std;

const int MX = 2e5 + 5;
const int MOD = 1e9 + 7;

int modPow(int base, int po) {
	int ret = 1;
	while(po) {
		if(po & 1) ret = 1ll * ret * base % MOD;
		base = 1ll * base * base % MOD;
		po >>= 1;
	}
	return ret;
}

int fact[MX], inve[MX];

void precompute() {
	fact[0] = inve[0] = 1;
	for(int i = 1 ; i < MX ; i++)
		fact[i] = 1ll * fact[i-1] * i % MOD;
	inve[MX-1] = modPow(fact[MX-1], MOD-2);
	for(int i = MX-2 ; i >= 1 ; i--)
		inve[i] = 1ll * inve[i+1] * (i+1) % MOD;
}

int getCombination(int n, int k) {
	if(k < 0 || n < 0 || k > n) return 0;
	int ret = fact[n];
	ret = 1ll * ret * inve[k] % MOD;
	ret = 1ll * ret * inve[n-k] % MOD;

	return ret;
}

pair<int ,int> solve(int n) {
	int same = (n-1) / 2;
	int sisa = n-1 - same;

	long long ways = getCombination(2*n-1, same);
	ways = ways * getCombination(2*n-1-same, sisa) % MOD;
	ways = ways * getCombination(2*n-1-same-sisa, sisa) % MOD;

	return {n-1, ways};
}

int main() {
	precompute();

	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		int n; cin >> n;
		pair<int, int> ret = solve(n);

		cout << ret.first << " " << ret.second << "\n";
	}
	return 0;
}