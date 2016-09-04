#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 405;

int n;
string s;
int dp[N][N];
int dp2[N][N][2];

int ways(int pos,int sisa,int can) {
	if(pos < 0) return 0;
	if(sisa == 0) return pos == 0;
	int &ret = dp2[pos][sisa][can];
	if(ret != -1) return ret;
	ret = (2 * ways(pos+1,sisa-1,can)) % MOD;
	ret = (ret + ways(can ? max(0,pos-1) : pos-1,sisa-1,can)) % MOD;
	return ret;
}

int solve(int pos,int sisa) {
	if(pos == s.length()) return ways(0,sisa,0);
	int &ret = dp[pos][sisa];
	if(ret != -1) return ret;
	ret = 0;
	for(int i = 0 ; i < sisa ; i++) {
		ret = (ret + 1ll * ways(0,i,pos == 0) * solve(pos+1,sisa-i-1)) % MOD;
		//cout << i << " " << ret << endl;
	}
	return ret;
}

int main() {
	cin >> n >> s;
	if(n <= 400) {
		memset(dp,-1,sizeof dp);
		memset(dp2,-1,sizeof dp2);
		cout << solve(0,n) << endl;
	}
	return 0;
}