#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL MOD = 1e9 + 7;
const int N = 405;

LL dp[N][N];
int a[N], b[N];
LL sumOfPow[N][N];
int n, c;

LL modPow(LL base,int po) {
	LL ret = 1;
	while(po) {
		if(po & 1) ret =(ret * base) % MOD;
		base = (base * base) % MOD;
		po >>= 1;
	}
	return ret;
}

void prec() {
	for(int po = 0 ; po < N ; po++)
		for(int i = 1 ; i < N ; i++) {
			sumOfPow[po][i] = (sumOfPow[po][i-1] + modPow(i,po)) % MOD;
		}
}

LL getSum(int x,int y,int z) {
	return (sumOfPow[z][y] - sumOfPow[z][x-1] + MOD) % MOD;
}

void read() {
	cin >> n >> c;
	for(int i = 0 ; i < n ; i++) {
		cin >> a[i];
	}
	for(int i = 0 ; i < n ; i++) {
		cin >> b[i];
	}
}

LL solve(int pos,int sisa) {
	if(pos == n) {
		if(sisa) return 0;
		return 1;
	}
	LL &ret = dp[pos][sisa];
	if(ret != -1) return ret;
	ret = 0;

	for(int i = 0 ; i <= sisa ; i++)
		ret = (ret + getSum(a[pos],b[pos],i) * solve(pos+1,sisa - i)) % MOD;

	return ret;
}

int main() {
	prec();
	read();
	memset(dp,-1,sizeof dp);
	cout << solve(0,c) << endl;
	return 0;
}