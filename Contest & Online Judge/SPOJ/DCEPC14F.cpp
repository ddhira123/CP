#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int LOG = 31;
const int M = 100;
const LL MOD = (LL)1e9 + 7;
const int N = (int)1e5 + 5;

LL mul[LOG][M];
LL dp[M];
int n,m,k,x;
int arr[N];

void compute() {
	memset(mul,0,sizeof mul);
	for(int i = 0 ; i < n ; i++) {
		mul[0][arr[i] % m]++;
	}
	for(int lg = 1 ; (1 << lg) <= k ; lg++) {
		for(int i = 0 ; i < m ; i++)
			for(int j = 0 ; j < m ; j++) {
				mul[lg][(i + j) % m] = (mul[lg][(i + j) % m] + mul[lg - 1][i] * mul[lg - 1][j]) % MOD;
			}
	}
}

void multiply(int lg) {
	LL temp[M];
	for(int i = 0 ; i < m ; i++)
		temp[i] = dp[i];
	memset(dp,0,sizeof dp);
	for(int i = 0 ; i < m ; i++)
		for(int j = 0 ; j < m ; j++)
			dp[(i + j) % m] = (dp[(i + j) % m] + mul[lg][i] * temp[j]) % MOD;
}

void power() {
	memset(dp,0,sizeof dp);
	dp[0] = 1;
	for(int i = 0 ; k > 0 ; i++)
		if(k & (1 << i)) {
			multiply(i);
			k -= (1 << i);
		}
}

void read() {
	scanf("%d",&n);
	for(int i = 0 ; i < n ; i++) {
		scanf("%d",arr + i);
	}
	scanf("%d %d %d",&m,&k,&x);
}

int main() {
	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		compute();
		power();
		printf("%lld\n",dp[x]);
	}
	return 0;
}