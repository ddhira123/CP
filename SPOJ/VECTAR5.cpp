#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N  = 1e6;

int dp[N + 1][4];

void add(int &x,int y) {
	x += y;
	if(x >= MOD) x -= MOD;
}

void precompute() {
	dp[0][3] = 1;
	for(int i = 1 ; i <= N ; i++)
		for(int j = 0 ; j < 4 ; j++) {
			add(dp[i][j],dp[i-1][j]);
			add(dp[i][j],dp[i-1][j | 1]);
			add(dp[i][j],dp[i-1][j | 2]);
			add(dp[i][j],dp[i-1][j]);
		}
}

int main() {
	precompute();
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		int n; scanf("%d",&n);
		printf("%d\n",dp[n][0]);
	}
	return 0;
}