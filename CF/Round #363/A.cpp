#include <bits/stdc++.h>
using namespace std;

int dp[105][3];
int arr[105];
int n;

int solve(int x,int lst) {
	if(x == n) return 0;
	int &ret = dp[x][lst];
	if(ret != -1) return ret;
	ret = 1 + solve(x+1,2);
	if((arr[x] & 1) && lst != 0)
		ret = min(ret,solve(x+1,0));
	if((arr[x] & 2) && lst != 1)
		ret = min(ret,solve(x+1,1));
	return ret;
}

int main() {
	memset(dp,-1,sizeof dp);
	cin >> n;
	for(int i = 0 ; i < n ; i++)
		cin >> arr[i];
	cout << solve(0,2) << endl;
	return 0;
}