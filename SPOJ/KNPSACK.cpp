#include <bits/stdc++.h>
using namespace std;

const int MX = 20000;
const int N = 100;

int dp[N][MX + 1];
int x,n;
int cost[N],weight[N];

int solve(int pos,int duit){
	if(pos == n)
		return 0;
	int &ret = dp[pos][duit];
	if(ret != -1) return ret;
	ret = solve(pos + 1,duit);
	if(duit >= cost[pos])
		ret = max(ret,solve(pos,duit - cost[pos]) + weight[pos]);
	ret = min(ret,x);
	return ret;		
}

int main(){
	scanf("%d %d",&x,&n);
	for(int i = 0 ; i < n ; i++){
		double temp;
		scanf("%d %lf",&weight[i],&temp);
		cost[i] = (int)(temp * 100 + 1e-9);
	}
	memset(dp,-1,sizeof dp);
	int ans = -1;
	for(int i = 0 ; i <= MX ; i++)
		if(solve(0,i) == x){
			ans = i;
			break;
		}
	assert(ans != -1);
	printf("%d.%02d\n",ans / 100,ans % 100);	
	return 0;
}
