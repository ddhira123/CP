#include <bits/stdc++.h>
using namespace std;

int dp[16][16];
int cost[16][16];
int mask[16];
string s[16];
int n;

void precompute() {
	for(int i = 0 ; i < n ; i++) {
		mask[i] = 0;
		for(int j = 0 ; j < n ; j++)
			mask[i] |= ((s[i][j] - '0') << j);
	}
	for(int i = 0 ; i < (1<<n) ; i++)
		for(int j = 0 ; j < (1<<n) ; j++) {
			cost[i][j] = 0;
			for(int k = 0 ; k < n ; k++)
				if(i & (1<<k)) {
					for(int l = 0 ; l < n ; l++)
						if(j & (1<<l))
							cost[i][j] += (s[k][l] == '0');
				}
		}
}

int solve(int worker,int machine) {
	if(worker == (1<<n) - 1) return 0;
	int &ret = dp[worker][machine];
	if(ret != -1) return ret;

	ret = 1e9;
	for(int i = 1 ; i < (1<<n) ; i++)
		if((worker & i) == 0)
			for(int j = 1 ; j < (1<<n) ; j++)
				if((machine & j) == 0 && __builtin_popcount(i) == __builtin_popcount(j)) {
					bool valid = 1;
					for(int k = 0 ; k < n ; k++)
						if(i & (1<<k))
							valid &= ((mask[k] | j) == j);
						else
							valid &= ((mask[k] & j) == 0);
					if(valid) {
						//printf("%d %d add %d %d cost %d\n",worker,machine,i,j,cost[i][j]);
						ret = min(ret,cost[i][j] + solve(worker + i,machine + j));
					}
				}
	//printf("%d %d %d\n",worker,machine,ret);
	return ret;			
}

int main() {
	int t; cin >> t;
	for(int tc = 1 ; tc <= t ; tc++) {
		cin >> n;
		for(int i = 0 ; i < n ; i++)
			cin >> s[i];
		memset(dp,-1,sizeof dp);
		precompute();
		printf("Case #%d: %d\n",tc,solve(0,0));
	}
	return 0;
}