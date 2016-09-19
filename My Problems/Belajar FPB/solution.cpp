#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
const int K = 500;
const int MX = 1e5;
const int MOD = 1e9 + 7;

int C[K+5][K+5];
long long cnt[MX + 5];
int memo[N + 5];
int arr[N + 5];
int n, k;

void precompute() {
	for(int i = 0 ; i <= K ; i++) {
		C[i][0] = 1;
		for(int j = 1 ; j <= i ; j++)
			C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
	}
}

long long modPow(long long base,int po) {
	long long ret = 1;
	while(po) {
		if(po & 1) ret = (ret * base) % MOD;
		base = (base * base) % MOD;
		po >>= 1;
	}
	return ret;
}

long long comb(int a,int b) {
	if(b > a || a < 0 || b < 0) return 0;
	return C[a][b];
}

long long calc(int bisa) {
	if(memo[bisa] != -1) return memo[bisa];

	int sisa = n - bisa;
	long long val = 0;
	for(int taken = k ; taken >= 0 ; taken--) {
		// 1 termasuk
		long long take1 = (modPow(taken+1,bisa) * modPow(taken,sisa)) % MOD;
		take1 = (take1 * comb(k-1,taken-1));
		// 1 gak termasuk
		long long take0 = (modPow(taken+1,n)) % MOD;
		take0 = (take0 * comb(k-1,taken));

		long long add = (take0 + take1) % MOD;
		if((k - taken) & 1)
			val = (val + MOD - add) % MOD;
		else
			val = (val + add) % MOD;
	}
	
	return memo[bisa] = val;
}

void read() {
	scanf("%d %d",&k,&n);
	for(int i = 0 ; i < n ; i++) {
		scanf("%d",arr + i);
	}
}

int solve() {
	memset(cnt,0,sizeof cnt);

	for(int i = 0 ; i < n ; i++)
		cnt[arr[i]]++;

	for(int i = 0 ; i <= n ; i++)
		memo[i] = -1;

	for(int i = 1 ; i <= MX ; i++)
		for(int j = i + i ; j <= MX ; j += i)
			cnt[i] += cnt[j];

	for(int i = MX ; i >= 1 ; i--) {
		int bisa = cnt[i];
		int sisa = n - cnt[i];

		cnt[i] = calc(bisa);
	
		for(int j = i + i ; j <= MX ; j += i)
			cnt[i] = (cnt[i] + MOD - cnt[j]) % MOD;
	}

	long long ret = 0;
	for(int i = 1 ; i <= MX ; i++)
		ret = (ret + i * cnt[i]) % MOD;

	return (ret * k) % MOD;	
}

int main() {
	precompute();

	int t; scanf("%d",&t);
	for(int tc = 1 ; tc <= t ; tc++) {
		read();
		printf("%d\n",solve());
	}
	return 0;
}