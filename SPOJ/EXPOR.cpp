#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long LLU;

const int MX = 31;
const LLU ONE = 1;

LLU C2(LLU x) {
	if(x == 0) return 0;
	return x * (x-1) / 2;
}

LLU fpb(LLU a,LLU b) {
	return b == 0 ? a : fpb(b,a % b);
}

int cnt[MX];
int n;

void add(int x) {
	for(int i = 0 ; i < MX ; i++)
		if(x & (1<<i))
			cnt[i]++;
}

int main() {
	int t; scanf("%d",&t);

	for(int tc = 1 ; tc <= t ; tc++) {
		scanf("%d",&n);

		for(int i = 0 ; i < MX ; i++) cnt[i] = 0;
		for(int i = 0 ; i < n ; i++) {
			int x; scanf("%d",&x);
			add(x);
		}

		LLU atas = 0;
		LLU bawah = C2(n);

		for(int i = 0 ; i < MX ; i++) {
			LLU pair10 = 1ll * cnt[i] * (n-cnt[i]);
			LLU pair11 = C2(cnt[i]);

			atas += (pair11 + pair10)*(1<<i);
		}

		LLU gcd = fpb(atas,bawah);
		printf("%llu/%llu\n",atas/gcd,bawah/gcd);
	}
	return 0;
}