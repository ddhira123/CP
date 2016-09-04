#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL MOD = (LL)1e9 + 7;
const int N = 1005;

int r,c,x,y;

LL dp[N][N];
LL fact[N];
LL inve[N];

void add(LL &a,LL b) {
	a += b;
	a %= MOD;
}

LL modPow(LL base,int po) {
	LL res = 1;
	while(po) {
		if(po & 1) res = (res * base) % MOD;
		base = (base * base) % MOD;
		po >>= 1;
	}
	return res;
}

void pre() {
	fact[0] = inve[0] = 1;
	for(int i = 1 ; i < N ; i++) {
		fact[i] = (fact[i - 1] * i) % MOD;
		inve[i] = modPow(fact[i],MOD - 2);
	}
}

void DP() {
	dp[0][0] = 1;
	for(int merah = 0 ; merah < r ; merah++)
		for(int merah_doang = 0 ; merah_doang <= c ; merah_doang++) {
			int bebas = c - merah - merah_doang;
			int biru = merah;
			int biru_doang = c - bebas - biru;

			// pasang merah di merah_doang, biru di biru_doang
			if(merah_doang > 0 && biru_doang > 0)
				add(dp[merah + 1][merah_doang - 1],dp[merah][merah_doang] * merah_doang * biru_doang);
			// pasang merah di merah_doang, biru di bebas
			if(merah_doang > 0 && bebas > 0)
				add(dp[merah + 1][merah_doang],dp[merah][merah_doang] * merah_doang * bebas);
			// pasang merah di bebas, biru di biru_doang
			if(bebas > 0 && biru_doang > 0)
				add(dp[merah + 1][merah_doang],dp[merah][merah_doang] * bebas * biru_doang);
			// pasang merah di bebas, biru di bebas
			if(bebas > 1)
				add(dp[merah + 1][merah_doang + 1],dp[merah][merah_doang] * (bebas) * (bebas - 1));
		}
}


int main() {
	cin >> r >> c >> x >> y;
	DP();
	pre();

	LL ans = 0;
	for(int paired = 0 ; paired <= r ; paired++) {
		int merah_doang = x - paired;
		int biru_doang = y - paired;
		int sisa_kolom = c - paired;
		int sisa_row = r - paired;
		int kosong = r - merah_doang - biru_doang - paired;

		//cout << paired << " " << merah_doang << " " << biru_doang << " " << sisa_kolom << " " << sisa_row << endl;
		if(merah_doang < 0 || biru_doang < 0 || sisa_row < merah_doang + biru_doang || sisa_kolom < merah_doang
			|| sisa_kolom < biru_doang) {
			continue;
		}

		LL tot = 0;
		for(int i = 0 ; i <= c ; i++)
			tot = (tot + dp[paired][i]) % MOD;

		// permutasi row merah doang
		tot = (tot * fact[sisa_kolom]) % MOD;
		tot = (tot * inve[sisa_kolom - merah_doang]) % MOD;
		// permutasi row biru doang
		tot = (tot * fact[sisa_kolom]) % MOD;
		tot = (tot * inve[sisa_kolom - biru_doang]) % MOD;

		// ngatur semua row
		tot = (tot * fact[r]) % MOD;
		tot = (tot * inve[paired]) % MOD;
		tot = (tot * inve[merah_doang]) % MOD;
		tot = (tot * inve[biru_doang]) % MOD;
		tot = (tot * inve[kosong]) % MOD;

		//cout << paired << " " << tot << endl;
		ans = (ans + tot) % MOD;
	}
	cout << ans << endl;
	return 0;
}