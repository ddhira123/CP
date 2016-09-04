#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 5005;

int dp[N][N];
string s;
int n;

int solve(int pos,int sisa) {
	if(sisa == 0) return pos == s.length();
	int &ret = dp[pos][sisa];
	if(ret != -1) return ret;
	ret = 0;
	ret = solve(pos+1,sisa-1);
	if(pos > 0) ret = (ret + 2ll * solve(pos-1,sisa-1)) % MOD;
	else ret = (ret + solve(pos,sisa-1)) % MOD;
	return ret;
}

int main() {
	cin >> n >> s;
	memset(dp,-1,sizeof dp);
	cout << solve(0,n) << endl;
	return 0;
}