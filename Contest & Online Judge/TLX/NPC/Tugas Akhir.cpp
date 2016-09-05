#include <bits/stdc++.h>
using namespace std;

const int MX = 30;
const long long MOD = (long long)1e9 + 7;

int bit[MX + 1];
int n;

int main(){
	ios_base::sync_with_stdio(0);
	cin >> n;
	for(int i = 0 ; i < n ; i++){
		int x;
		cin >> x;
		for(int iter = 0 ; iter <= MX ; iter++)
			if(x & (1 << iter))
				bit[iter]++;
	}
	long long ans = 0;
	for(int i = 0 ; i <= MX ; i++){
		long long cnt = bit[i];
		//cout << i << " " << cnt << endl;
		cnt *= (cnt - 1);
		cnt /= 2LL;
		cnt %= MOD;
		cnt *= (1LL << i);
		cnt %= MOD;
		ans = (ans + cnt) % MOD;
	}
	cout << ans << endl;
	return 0;
}
