#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 205;

double dp[N][N][N];
double arr[N];
int n,k;

double solve(int pos,int menang,int kalah) {
	if(menang + kalah == k) {
		return menang == kalah;
	}
	if(pos == n) return 0;
	double &ret = dp[pos][menang][kalah];
	if(ret > -1500) return ret;
	ret = -1000;
	for(int i = pos+1 ; i <= n ; i++) {
		ret = max(ret,arr[pos] * solve(i,menang+1,kalah) + (1-arr[pos]) * solve(i,menang,kalah+1));
	}
	return ret;
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%d %d",&n,&k);
		for(int i = 0 ; i < n ; i++) {
			scanf("%lf",&arr[i]);
			for(int j = 0 ; j <= n ; j++)
				for(int l = 0 ; l <= n ; l++) {
					dp[i][j][l] = -2000;
				}
		}
		double res = -1;
		for(int i = 0 ; i < n ; i++)
			res = max(res,solve(i,0,0));
		printf("Case #%d: %.10lf\n",tc,res);
	}
	return 0;
}