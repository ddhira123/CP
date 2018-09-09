#include <bits/stdc++.h>
using namespace std;

const int N = 100000;
typedef long long LL;

LL arr[N + 5];
LL pxor[N + 5];
int n,q;

LL getVal(int idx) {
	return idx < 0 ? 0 : pxor[idx];
}

void init() {
	scanf("%d",&n);
	for(int i = 0 ; i < n ; i++) {
		scanf("%lld",arr + i);
		arr[n] ^= arr[i];
	}
	n++;
	pxor[0] = arr[0];
	for(int i = 1 ; i < n ; i ++)
		pxor[i] = arr[i] ^ pxor[i - 1];
}

void solve() {
	scanf("%d",&q);
	while(q--) {
		LL l,r;
		scanf("%lld %lld",&l,&r);
		l--; r--;

		LL modL = l % n;
		LL modR = r % n;
		LL blockL = l / n;
		LL blockR = r / n;

		if(blockL == blockR) {
			printf("%lld\n",getVal(modR) ^ getVal(modL - 1));
		}
		else {
			LL kiri = getVal(n-1) ^ getVal(modL - 1);
			LL kanan = getVal(modR);
			printf("%lld\n",kiri ^ kanan);
		}
	}
}

int main() {
	init();
	solve();
	return 0;
}