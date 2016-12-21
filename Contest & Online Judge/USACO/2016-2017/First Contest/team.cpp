/**
	O(NMK)
	AC
*/
#include <bits/stdc++.h>
using namespace std;

void OPEN(string s) {
	freopen((s + ".in").c_str(),"r",stdin);
	freopen((s + ".out").c_str(),"w",stdout);
}

void CLOSE() {
	fclose(stdin);
	fclose(stdout);
}

const int N = 1e3 + 5;
const int MOD = 1e9 + 9;

int fp[N], fj[N];
int dp[2][N][N];
int n, m, k;

void read() {
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d",fj + i);
	for(int i = 1 ; i <= m ; i++)
		scanf("%d",fp + i);
}

int solve() {
	sort(fj + 1,fj + n + 1);
	sort(fp + 1,fp + m + 1);

	for(int i = 0 ; i <= n ; i++)
		for(int j = 0 ; j <= m ; j++)
			dp[0][i][j] = 1;

	for(int iter = 1 ; iter <= k ; iter++) {
		int bit = iter & 1;
		int prv = bit ^ 1;
		for(int i = 0 ; i <= n ; i++)
			dp[bit][i][0] = 0;
		for(int j = 0 ; j <= m ; j++)
			dp[bit][0][j] = 0;

		for(int i = 1 ; i <= n ; i++)
			for(int j = 1 ; j <= m ; j++) {
				int &ret = dp[bit][i][j];
				ret = 0;

				if(fj[i] > fp[j]) {
					//printf("%d\n",dp[prv][i-1][j-1]);
					ret = dp[prv][i-1][j-1];
				}
				ret = (ret + dp[bit][i-1][j]) % MOD;
				ret = (ret + dp[bit][i][j-1]) % MOD;
				ret = (ret + MOD - dp[bit][i-1][j-1]) % MOD;

				//printf("iter %d i %d j %d dp %d\n",iter,i,j,ret);
			}
	}
	return dp[k & 1][n][m];
}

int main() {
	OPEN("team");
	read();
	printf("%d\n",solve());
	CLOSE();
	return 0;
}