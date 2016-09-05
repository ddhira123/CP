#include <bits/stdc++.h>
using namespace std;

const int N = 40;
const int LMT = 17;
const int MOD = 1e9 + 7;

long long modPow(long long base,int po) {
	long long ret = 1;
	while(po) {
		if(po & 1) ret = (ret * base) % MOD;
		base = (base * base) % MOD;
		po >>= 1;
	}
	return ret;
}

int pwr[N+5];
int dp[N+1][1<<LMT];
int x,y,z,n;

void prec() {
	pwr[0] = 1;
	for(int i = 1;  i <= N ; i++) {
		pwr[i] = (10ll * pwr[i-1]) % MOD;
		//cout << i << pwr[i] << endl;
	}
	memset(dp,-1,sizeof dp);
}

int solve(int sisa,int msk) {
	if(sisa == 0) return 0;
	int &ret = dp[sisa][msk];
	if(ret != -1) return ret;
	ret = 0;
	for(int i = 1 ; i <= 10 ; i++) {
		int zz = z - i;
		int yz = zz + y;
		int xyz = yz + x;
		if(zz >= 0 && (msk & (1<<zz)) > 0 && (msk & (1<<yz)) > 0 && (msk & (1<<xyz)) > 0)
			ret = (ret + pwr[sisa-1]) % MOD;
		else {
			int nexMask = msk << i;
			nexMask &= ((1<<LMT) - 1);
			nexMask |= 1;
			ret = (ret + solve(sisa-1,nexMask)) % MOD;
		}
	}
	return ret;
}

int main() {
	prec();
	cin >> n >> x >> y >> z;
	cout << solve(n,1) << endl;
	return 0;
}