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
	for(int i = 1 ; i < (1<<n) ; i++)
		if(__builtin_popcount(i) == k) {
			arr.clear();
			for(int j = 0 ; j < n ; j++)
				if(i & (1<<j))
					arr.push_back(tmp[j]);

			for(int j = 0 ; j <= k ; j++)
				for(int l = 0 ; l <= k ; l++)
					dp[j][l] = -1.0;
			ans = max(ans,solve(0,0));
		}
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