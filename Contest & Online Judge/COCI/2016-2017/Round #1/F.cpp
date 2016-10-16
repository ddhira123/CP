#include <bits/stdc++.h>
using namespace std;

const int N = 16;
const int MX = 1e6 + 5;
const int INF = 1e9;

int sums[1<<N][26];
int realSum[1<<N];
char s[MX];
int dp[1<<N];
int n;

void init() {
	scanf("%d",&n);
	for(int i = 0 ; i < n ; i++) {
		scanf("%s",s);
		int len = strlen(s);
		int bit = 1<<i;
		for(int j = 0 ; j < len ; j++)
			sums[bit][s[j]-'a']++;
	}
	for(int i = 1 ; i < (1<<n) ; i++) {
		dp[i] = INF;
		int lsb = i & -i;
		if(lsb != i) {
			for(int j = 0 ; j < 26 ; j++)
				sums[i][j] = min(sums[lsb][j], sums[i-lsb][j]);
		}
		for(int j = 0 ; j < 26 ; j++) {
			//sums[i][j] = min(sums[lsb][j], sums[i - lsb][j]);
			realSum[i] += sums[i][j];
		}
		//printf("%d -> %d\n",i,realSum[i]);
	}
}

int solve(int msk) {
	if(msk == (msk & -msk)) return realSum[msk];
	int &ret = dp[msk];
	if(ret != INF) return ret;
	ret = INF-1;

	int add = -realSum[msk];
	for(int i = msk & (msk-1) ; i > 0 ; i = msk & (i-1))
		ret = min(ret,add + solve(i) + solve(msk-i));
	return ret;
}

int main() {
	init();
	printf("%d\n",solve((1<<n)-1)+1);
	return 0;
}