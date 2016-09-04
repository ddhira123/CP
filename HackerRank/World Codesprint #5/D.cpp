#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int  MX = 5e5 + 5;
const LL MOD = 1e9 + 7;

LL modPow(LL base,int po) {
	LL ret = 1;
	while(po) {
		if(po & 1) ret = (ret * base) % MOD;
		base = (base * base) % MOD;
		po >>= 1;
	}
	return ret;
}

LL fact[MX];
LL inve[MX];

void prec() {
	fact[0] = inve[0] = 1;
	for(int i = 1 ; i < MX ; i++)  {
		//cout << i << endl;
		fact[i] = (fact[i-1] * i) % MOD;
	}
	inve[MX-1] = modPow(fact[MX-1],MOD-2);
	for(int i = MX-2 ; i >= 1 ; i--) {
		//cout << i << endl;
		inve[i] = (inve[i+1] * (i+1)) % MOD;
	}
	//cout << "beres\n";
}

LL comb(int n,int k) {
	//cout << n << " " << k << endl;
	if(n < 0 || k < 0 || n < k) return 0;
	//cout << "hore\n";
	LL ret = (fact[n] * inve[k]) % MOD;
	return (ret * inve[n-k]) % MOD;
}

int main() {
	prec();
	int t; cin >> t;

	for(int tc = 1 ; tc <= t ; tc++) {
		int n, m;
		cin >> m >> n;

		LL ans = 0;
		LL invert = modPow(n,MOD-2);
		LL mul = 1;
		LL setelah = modPow(n,m-n);

		for(int en = n ; en <= m ; en++) {
			//cout << en << endl;
			int bebas_setelah = m - en;
			int bebas_sebelum = en - n;

			LL add = mul;
			add = (add * setelah) % MOD;
			add = (add * comb(en-1,n-1)) % MOD;

			setelah = (setelah * invert) % MOD;
			mul = (mul * (n-1)) % MOD;

			ans = (ans + add) % MOD;
		}

		cout << ans << endl;
	}
	return 0;
}