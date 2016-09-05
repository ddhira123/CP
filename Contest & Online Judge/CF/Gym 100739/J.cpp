#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second

const int N = 34;
const int R = 5005;
string str;
int n,lmt,budget;
LL cost[N][N];
LL dpCost[N][N];
int dp[N / 2][N][N / 2][N][N / 2];

LL getCost(int l,int r) {
	if(l > r) return 0;
	LL &ret = dpCost[l][r];
	if(ret != -1) return ret;
	ret = cost[l][r] + getCost(l + 1,r) + getCost(l,r - 1) - getCost(l + 1,r - 1);
	return ret;
}

LL solve(int sisa,int lkiri,int llen,int rkanan,int rlen) {
	int lkanan = lkiri + llen;
	int rkiri = rkanan - rlen;
	if(sisa == 0) return 0;
	if(lkanan >= rkiri) return budget + 1;
	LL ret = dp[sisa][lkiri][llen][rkanan][rlen];

	if(ret != -1) return ret;
	ret = budget + 1;
	// l maju
	ret = min(ret,solve(sisa,lkiri + llen + 1,0,rkanan,rlen));
	// r maju
	ret = min(ret,solve(sisa,lkiri,llen,rkanan - rlen - 1,0));
	// match
	if(str[lkanan] == str[rkiri]) {
		LL kurang = getCost(lkiri,lkanan - 1) + getCost(rkiri + 1,rkanan);
		LL dcost = getCost(lkiri,lkanan) + getCost(rkiri,rkanan);
		if(lkanan + 1 == rkiri)
			dcost = getCost(lkiri,rkanan);
		ret = min(ret,dcost - kurang + solve(sisa - 1,lkiri,llen + 1,rkanan,rlen + 1));
	}
	return dp[sisa][lkiri][llen][rkanan][rlen] = ret;
}

int main() {
	cin >> n >> lmt >> budget;
	cin >> str;
	str = "." + str;
	for(int i = 0 ; i < lmt ; i++) {
		int l,r,c;
		cin >> l >> r >> c;
		cost[l][r] += c;
	}
	int best = 0;
	memset(dp,-1,sizeof dp);
	memset(dpCost,-1,sizeof dpCost);
	for(int i = 1 ; i <= n / 2 ; i++)
		if(solve(i,1,0,n,0) <= budget)
			best = i*2;
	cout << best << endl;		
	return 0;
}