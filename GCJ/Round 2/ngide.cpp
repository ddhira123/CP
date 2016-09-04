#include <bits/stdc++.h>
using namespace std;

vector<double> arr;
double tmp[20];
double dp[20][20];
int n,k;

double solve(int pos,int menang) {
	if(pos == k) {
		return menang == (k / 2);
	}
	double &ret = dp[pos][menang];
	if(ret > -0.5) return ret;
	ret = arr[pos] * solve(pos+1,menang+1);
	ret = ret + (1-arr[pos]) * solve(pos+1,menang);
	return ret;
}

double brute() {
	double ans = -1;
	sort(tmp,tmp + n);
	arr.clear();
	for(int i = 0 ; i < k/2 ; i++) {
		arr.push_back(tmp[k - i - 1]);
		arr.push_back(tmp[i]);
	}
	memset(dp,-1,sizeof dp);
	ans = solve(0,0);
	return ans;	
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%d %d",&n,&k);
		for(int i = 0 ; i < n ; i++) {
			scanf("%lf",&tmp[i]);
		}
		double res = brute();
		printf("Case #%d: %.10lf\n",tc,res);
	}
	return 0;
}