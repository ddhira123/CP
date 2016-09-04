#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL MOD = 1e9 + 7;
const int N = 1000005;

LL C2(LL x) {
	LL ret = x * (x-1) / 2;
	return ret % MOD;
}

LL C4(LL x) {
	if(x < 4) return 0;
	vector<LL> v = {x,x-1,x-2,x-3};
	vector<LL> d = {1,2,3,2,2};
	for(int i = 0 ; i < d.size() ; i++)
		for(int j = 0 ; j < v.size() ; j++)
			if(v[j] % d[i] == 0) {
				v[j] /= d[i];
				break;
			}

	LL ret = 1;
	for(int i = 0 ; i < v.size() ; i++)
		ret = (ret * v[i]) % MOD;

	return ret;		
}

LL cnt[30];
LL kurang[30][30];
LL kurangSQR[30][30];
LL kurangBiasa[30][30];

char s[N];

int main() {
	scanf("%s",s);
	int len = strlen(s);

	LL ans = 0;
	for(int i = 0 ; i < len ; i++) {
		int idx = s[i] - 'a';
		LL bef = cnt[idx];

		LL add = 0;
		for(int j = 0 ; j < 26 ; j++) {
			if(j == idx) continue;
			LL occ = cnt[j];
			LL plus = (C2(occ) * bef) % MOD;
			plus = (plus - kurang[idx][j]) % MOD;
			plus = (plus + kurangSQR[idx][j]) % MOD;
			plus = (plus - kurangBiasa[idx][j] * occ) % MOD;

			add = (add + plus) % MOD;
		}

		ans = (ans + add) % MOD;
		cnt[idx]++;
		for(int j = 0 ; j < 26 ; j++) {
			if(j == idx) continue;
			kurang[idx][j] = (kurang[idx][j] + C2(cnt[j])) % MOD;
			kurangSQR[idx][j] = (kurangSQR[idx][j] + cnt[j]*cnt[j]) % MOD;
			kurangBiasa[idx][j] = (kurangBiasa[idx][j] + cnt[j]) % MOD;
		}
	}
	for(int i = 0 ; i < 26 ; i++)
		ans = (ans + C4(cnt[i])) % MOD;
	if(ans < 0) ans += MOD;
	printf("%lld\n",ans);
	return 0;
}