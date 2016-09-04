#include <bits/stdc++.h>
using namespace std;

unsigned long long dp[105][2];
int n;

unsigned long long solve(int x,int stat) {
	if(x == 0) return stat;
	unsigned long long &ret = dp[x][stat];
	if(ret != -1) return ret;
	ret = 0;
	for(int i = 1 ; i <= x ; i++)
		ret += solve(x - i,stat || (i == n)) * 3;
	//cout << x << " " << stat << " " << ret << endl;
	return ret;
}

int main() {
	cin >> n;
	memset(dp,-1,sizeof dp);
	int len = 2 * n - 2;
	cout <<  (solve(len,0) / 3ll) * 4ll << endl;
	return 0;
}