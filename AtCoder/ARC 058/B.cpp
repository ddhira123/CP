#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int MOD = 1e9 + 7;

long long fact[N];
long long inve[N];

long long modPow(long long base,int po) {
	long long ret = 1;
	while(po) {
		if(po & 1) ret = (ret * base) % MOD;
		base = (base * base) % MOD;
		po >>= 1;
	}
	return ret;
}

void prec() {
	fact[0] = inve[0] = 1;
	for(int i = 1 ; i < N ; i++) {
		fact[i] = (fact[i-1] * i) % MOD;
		inve[i] = modPow(fact[i],MOD-2);
	}
}

long long comb(int x,int y) {

	if(x <0 || y < 0 || x < y) return 0;
	long long res = (fact[x] * inve[y]) % MOD;
	res =  (res * inve[x-y]) % MOD;
	//cout << x << " " << y <<  " " << res << endl;
	return res;
}

int main() {
	prec();

	int h, w, a , b;
	cin >> h >> w >> a >> b;
	int bawah = h-a;
	int col = b;
	long long ans = 0;

	for(int i = bawah ; i >= 1 ; i--) {
		int sisa_row = h - i;
		int sisa_col = w-b;
		long long ways = (comb(i-1+col-1,col-1) * comb(sisa_row+sisa_col-1,sisa_col-1)) % MOD;

		ans = (ans + ways) % MOD;
	}
	cout << ans << endl;
	return 0;
}