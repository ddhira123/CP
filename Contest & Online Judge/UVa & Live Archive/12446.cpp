#include <bits/stdc++.h>
using namespace std;

const int N = 100001;
const int K = 101;
const int INF = (int)1e9;

int cnt;
int in[N],ot[N];
int dp[N][K];
int val[N];
int inve[N];
vector<int> chld[N];
int n,k;

void dfs(int u){
	in[u] = ++cnt;
	inve[cnt] = u;
	for(int v : chld[u])
		dfs(v);
	ot[u] = cnt;
}

int DP(){
	for(int i = 0 ; i < n ; i++){
		int u = inve[i];
		for(int j = 0 ; j <= k ; j++)
			dp[i + 1][j] = max(dp[i + 1][j],dp[i][j]);
		for(int j = 0 ; j < k ; j++)
			dp[ot[u] + 1][j + 1] = max(dp[ot[u] + 1][j + 1],dp[i][j] + val[u]);	
	}
	int ans = -INF;
	for(int i = 1 ; i <= k ; i++)
		ans = max(ans,dp[n][i]);
	return ans;	
}

int main(){
	scanf("%d %d",&n,&k);
	while(n | k){
		for(int i = 0 ; i <= n ; i++){
			chld[i].clear();
			for(int j = 1 ; j <= k ; j++)
				dp[i][j] = -INF;
		}
		for(int i = 0 ; i < n ; i++)
			scanf("%d",&val[i]);
		for(int i = 1 ; i < n ; i++){
			int papa;
			scanf("%d",&papa);
			chld[papa].push_back(i);
		}	
		cnt = -1;
		dfs(0);
		printf("%d\n",DP());
		scanf("%d %d",&n,&k);
	}
	return 0;
}
