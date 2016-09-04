#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

int dp[N][2];
vector<int> chld[N];
int arr[N];

int solve(int pos,int stat){
	int &ret = dp[pos][stat];
	if(ret != -1) return ret;
	ret = (int)1e9;
	//pasang 0
	if(stat != 1){
		int sum = arr[pos];
		for(int nex : chld[pos])
			sum += solve(nex,0);
		ret = min(ret,sum);	
	}
	//pasang 1
	int sum = 1 - arr[pos];
	for(int nex : chld[pos])
		sum += solve(nex,1);
	ret = min(ret,sum);
	return ret;	
}

int main(){
	int tc;
	scanf("%d",&tc);
	for(int t = 1 ; t <= tc ; t++){
		int n;
		scanf("%d",&n);
		for(int i = 1 ; i <= n ; i++){
			chld[i].clear();
			dp[i][0] = dp[i][1] = -1;
		}
		for(int i = 1 ; i <= n ; i++){
			int papa;
			scanf("%d",&papa);
			chld[papa].push_back(i);
		}
		for(int i = 1 ; i <= n ; i++)
			scanf("%d",&arr[i]);
		printf("Case #%d: %d\n",t,solve(1,0));	
	}
	return 0;
}
