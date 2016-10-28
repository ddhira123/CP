#include <bits/stdc++.h>
using namespace std;

const int N = 3335;
const int MOD = 1e9 + 7;

int dp[N][N];
int dp2[N][N];
int psum[N][N];
int n, d, k, t;

int getSum(int a,int b) {
	int c = a-d;
	if(c < 0) return psum[a-1][b];
	return (psum[a-1][b] - psum[c][b] + MOD) % MOD;
}

int solve(int pos,int sisa);

int solve2(int pos,int sisa) {
	if(pos < 0 || sisa < 0) return 0;
	if(pos == 0) {
		if(sisa == 0) return 1;
		return 0;
	}
	int &ret = dp2[pos][sisa];
	if(ret != -1) return ret;
	return ret = (1ll * (k-1) * solve(pos-1,sisa) + solve2(pos-1,sisa-1)) % MOD;
}

int solve(int pos,int sisa) {
	if(pos < 0 || sisa < 0) return 0;
	if(pos == 0) {
		if(sisa == 0) return 1;
		return 0;
	}
	int &ret = dp[pos][sisa];
	if(ret != -1) return ret;
	ret = solve2(pos-d+1,sisa-1);
	ret = (ret + 1ll * (k-1) * getSum(pos,sisa)) % MOD;
	if(sisa == 0 && pos < d-1) ret = (ret+1) % MOD;
	return ret;
}

int work() {
	memset(dp,-1,sizeof dp);
	memset(dp2,-1,sizeof dp2);
	
	for(int pos = 0 ; pos <= n ; pos++)
		for(int sisa = 0 ; sisa <= t ; sisa++) {
			psum[pos][sisa] = solve(pos,sisa);
			//cout << pos << " " << sisa << " " << psum[pos][sisa] << "\n";
			if(pos) psum[pos][sisa] = (psum[pos][sisa] + psum[pos-1][sisa]) % MOD;
		}

	return (1ll * k * solve(n-1,t)) % MOD;	
}

int cornerCase() {
	if(t != n) return 0;
	int ret = 1;
	for(int i = 1 ; i <= n ; i++)
		ret = 1ll * ret * k % MOD;
	return ret;
}

int main() {
	cin >> n >> d >> t >> k;
	int ans = d == 1 ? cornerCase() : work();
	cout << ans << "\n";
	return 0;
}