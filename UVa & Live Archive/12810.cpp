#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL MOD = (LL)1e9 + 9;

LL modpow(LL base,int po){
	LL res = 1;
	while(po){
		if(po & 1) res = (res * base) % MOD;
		base = (base * base) % MOD;
		po >>= 1;
	}
	return res;
}

int main(){
	ios_base::sync_with_stdio(0);
	LL inve = modpow(2,MOD - 2);
	int tc;
	cin >> tc;
	while(tc--){
		int n;
		cin >> n;
		LL ans = 1;
		for(int i = 0 ; i < n ; i++){
			LL x;
			cin >> x;
			ans = (ans * (x * 2LL + 1)) % MOD;
		}
		ans--;
		ans = (ans * inve) % MOD;
		if(ans < 0) ans += MOD;
		cout << ans << "\n";
	}
	return 0;
}
