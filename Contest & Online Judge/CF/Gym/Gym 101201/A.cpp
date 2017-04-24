#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int LETTER = 26;

int dp[N][LETTER+1];
string s;

int solve(int pos, int x) {
	if(x == LETTER) return 0;
	if(pos == s.length()) return N;

	int &ret = dp[pos][x];
	if(ret != -1) return ret;

	ret = min(solve(pos+1, x), 1 + solve(pos, x+1));
	if(s[pos] == x + 'a')
		ret = min(ret, solve(pos, x+1));
	return ret;
}

int main() {
	cin >> s;
	memset(dp, -1, sizeof dp);
	cout << solve(0, 0) << endl;
	return 0;
}