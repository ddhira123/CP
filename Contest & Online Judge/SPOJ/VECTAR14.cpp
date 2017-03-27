#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const int MOD = 1000000007;

string s;
int dp[N][N];
int nxt[N][2];
int n;

int solve(int pos,int sum) {
	if(pos == n || sum < 0) return 0;
	int &ret = dp[pos][sum];
	if(ret != -1) return ret;

	ret = (sum == 0);
	ret += solve(nxt[pos][0],sum+1);
	ret += solve(nxt[pos][1],sum-1);
	ret %= MOD;

	return ret;
}

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		cin >> s;
		s = "(" + s;
		n = s.length();

		nxt[n-1][0] = nxt[n-1][1] = n;
		for(int i = n-1 ; i > 0 ; i--) {
			nxt[i-1][0] = nxt[i][0];
			nxt[i-1][1] = nxt[i][1];

			if(s[i] == '(') nxt[i-1][0] = i;
			else nxt[i-1][1] = i;
		}

		for(int i = 0 ; i < n ; i++)
			for(int j = 0 ; j <= i ; j++)
				dp[i][j] = -1;

		cout << solve(0,0) << "\n";
	}
	return 0;
}