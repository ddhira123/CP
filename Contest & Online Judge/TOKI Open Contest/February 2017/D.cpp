#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MOD = 1e9 + 8;
const int MX = 1e5 + 5;

int dp[20][MX];

vector<LL> val;
LL n, a, b;
string s;
LL pwr[MX];

int opt[30][30];

char ss[MX];

void init() {
	pwr[0] = 1;
	for(int i = 1 ; i < MX ; i++)
		pwr[i] = (pwr[i-1] * 10LL) % MOD;
}

void generate() {
	val.push_back(1);
	for(int i = 1 ; i <= n && val.back() != 0 ; i++) {
		LL lst = val.back();
		val.push_back((lst * a) % b);
	}
	while(val.size() > n) val.pop_back();
	assert(val.size() <= 20);

	for(int i = 0 ; i < val.size() ; i++)
		for(int j = 0 ; j < 10 ; j++)
			opt[i][j] = val[i] * j % b;
}

int getVal(string str) {
	LL ret = 0;

	reverse(str.begin(), str.end());
	for(int i = 0 ; i < min((int)val.size(), (int)str.length()); i++) {
		ret = (ret + val[i] * (str[i] - '0')) % b;
	}

	return ret;
}

int solve(int pos,int x) {
	//cout << pos << " " << x << "\n";
	if(pos == val.size()) {
		if(x != 0) {
			return 0;
		}
		return pwr[n-val.size()];
	}

	int &ret = dp[pos][x];
	if(ret != -1) {
		return ret;
	}

	ret = 0;
	for(int i = 0 ; i < 10 ; i++) {
		LL nexVal = x;
		nexVal -= val[pos] * i;
		nexVal %= b;
		nexVal = (nexVal + b) % b;
		ret = (ret + solve(pos+1, nexVal)) % MOD;
	}

	return ret;
}

int DP(int x) {
	dp[val.size()][0] = pwr[n-val.size()];

	for(int i = val.size()-1; i >= 0 ; i--) {
		for(int j = 0 ; j < b ; j++)
			for(int k = 0 ; k < 10 ; k++) {
				int nexVal = j;
				nexVal -= opt[i][k];
				nexVal = (nexVal + b) % b;

				dp[i][j] = (dp[i][j] + dp[i+1][nexVal]);
				if(dp[i][j] >= MOD) {
					dp[i][j] -= MOD;
				} 
			}
	}

	return dp[0][x];
}

int main() {
	init();
	scanf("%lld %lld %lld %s", &n, &a, &b, ss);
	s = (string)ss;

	generate();
	int val = getVal(s);

	int ret = (DP(val) - 1 + MOD) % MOD;

	cout << ret << "\n";
	return 0;
}