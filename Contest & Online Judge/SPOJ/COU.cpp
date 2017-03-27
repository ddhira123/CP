#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

char s[N];
int dp[2][N];
int t,n;

inline int getCost(char x) {
	return x == 'P' ? 1 : -1;
}

int DP() {
	int lg = 0;
	while((1 << lg) <= n) lg++;
	memset(dp[(lg+1) & 1],0,sizeof dp[(lg+1) & 1]);
	for(int iter = lg ; iter >= 0 ; iter--) {
		int bit = (iter & 1);
		int nex = (bit ^ 1);

		dp[bit][n] = 0;
		for(int i = n - 1 ; i >= 0 ; i--) {
			dp[bit][i] = getCost(s[i]) + dp[bit][i+1];
			dp[bit][i] = max(dp[bit][i],dp[nex][min(n,i + 1 + (1 << iter))] - 1);
		}
	}
	return dp[0][0];
}

int main() {
	scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%s",s);
		n = strlen(s);
		printf("%d\n",DP());
	}
	return 0;
}