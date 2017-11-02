#include <bits/stdc++.h>
using namespace std;

const int MX = 3000;
const int MOD = 1e9+7;

const string A = "kwetiauw";
const string B = "mihun";
const string C = "friedrice";

int comb[MX][MX];

void precompute() {
	for(int i = 0 ; i < MX ; i++) {
		comb[i][0] = 1;
		for(int j = 1 ; j <= i ; j++) {
			comb[i][j] = (comb[i-1][j] + comb[i-1][j-1]) % MOD;
		}
	}
}

int main() {
	precompute();
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		int n, a, b, c;
		cin >> n >> a >> b >> c;

		map<char, int> cnt;
		for(char x : A) cnt[x] += a;
		for(char x : B) cnt[x] += b;
		for(char x : C) cnt[x] += c;

		int sisa = a * A.length() + b * B.length() + c * C.length();
		long long ret = 1;

		for(auto it : cnt) {
			ret = (ret * comb[sisa][it.second]) % MOD;
			sisa -= it.second;
		}

		printf("Kasus #%d: %lld\n", tc, ret);
	}
	return 0;
}