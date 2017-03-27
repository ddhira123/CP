#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

double dp[N][N];
int n;
pair<int,int> arr[N];

void reset() {
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= n ; j++)
			dp[i][j] = -1.0;
}

double getDist(int a,int b) {
	return hypot(arr[a].first - arr[b].first,arr[a].second - arr[b].second);
}

double solve(int l,int r) {
	int maks = max(l,r);
	if(maks == n)
		return getDist(l,r);
	double &ret = dp[l][r];
	if(ret > -0.5) return ret;
	ret = min(solve(l,maks + 1) + getDist(r,maks + 1), solve(maks + 1,r) + getDist(l,maks + 1));
	return ret;
}

int main() {
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d %d",&arr[i].first,&arr[i].second);
	sort(arr + 1,arr + n + 1);
	reset();
	printf("%.2lf\n",solve(1,1));
	return 0;
}