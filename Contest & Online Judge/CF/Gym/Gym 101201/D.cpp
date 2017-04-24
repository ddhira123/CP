#include <bits/stdc++.h>
using namespace std;

const int N = 305;
const int MOD = 1e9 + 7;

int dp[N][N][N][2];
int fact[N];
int C[N][N];
int arr[N];
int n, k;

int modpow(int a,int b) {
	int ret = 1;
	while(b) {
		if(b & 1) ret = (ret * a) % MOD;
		a = 1ll * a * a % MOD;
		b >>= 1;
	}
	return ret;
}

int solve(int less_yet, int great_yet, int less_in, int taken) {
	if(taken == 1 && less_yet + great_yet == 0) {
		int great_in = k - less_in - 1;
		long long ret = less_yet + great_yet + great_in + 1;

		ret = (ret * fact[less_yet + great_yet]) % MOD;

		return ret;
	}

	if(taken == 1 && less_in == 0) {
		int great_in = k-1;
		long long ret = less_yet + great_yet + great_in + 1;

		ret = (ret * fact[less_yet + great_yet]) % MOD;

		return ret;
	}

	int &ret = dp[less_yet][great_yet][less_in][taken];
	if(ret != -1) return ret;

	ret = 0;
	if(!taken) {
		ret = (ret + solve(less_yet, great_yet, max(less_in-1, 0), 1)) % MOD;
	}
	if(great_yet > 0) {
		ret = (ret + 1ll * great_yet * solve(less_yet, great_yet-1, max(less_in-1, 0), taken)) % MOD;
	}
	if(less_yet > 0) {
		ret = (ret + 1ll * less_yet * solve(less_yet-1, great_yet, less_in, taken)) % MOD;
	}

	return ret;
}

void prepare() {
	memset(dp, -1, sizeof dp);
	fact[0] = 1;
	for(int i = 1 ; i < N ; i++)
		fact[i] = (1ll * i * fact[i-1]) % MOD;

	for(int i = 0 ; i < N ; i++) {
		C[i][0] = 1;
		for(int j = 1 ; j <= i ; j++)
			C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
	}
}

int calc(int pos) {
	for(int i = 0 ; i < pos ; i++)
		if(arr[i] == arr[pos]) return 0;

	int less_than = 0;
	int great_than = 0;
	int same = 0;

	for(int i = 0 ; i < n ; i++)
		if(arr[i] == arr[pos])
			same++;
		else if(arr[i] < arr[pos])
			less_than++;
		else if(arr[i] > arr[pos])
			great_than++;

	long long res = 0;

	for(int idx = 1; idx <= same ; idx++) {
		int cur_less_than = less_than + idx-1;
		int cur_great_than = great_than + (same-idx);

		long long mul = C[same-1][idx-1];
		mul = (mul * fact[idx-1]) % MOD;
		mul = (mul * fact[same-idx]) % MOD;

		long long lol = 0;

		// gak termasuk k awal
		for(int i = 0 ; i <= cur_less_than ; i++)
			for(int j = 0 ; j <= cur_great_than ; j++) {
				if(i + j != k) continue;

				int greats = C[cur_great_than][j];
				int lesss = C[cur_less_than][i];

				long long ret = greats;
				ret = (ret * lesss) % MOD;
				ret = (ret * fact[k]) % MOD;

				ret = (ret * solve(cur_less_than - i, cur_great_than - j, i, 0)) % MOD;

				lol = (lol + ret) % MOD;
			}

		// cout << res << endl;

		// termasuk k awal
		for(int i = 0 ; i <= cur_less_than ; i++)
			for(int j = 0 ; j <= cur_great_than ; j++) {
				if(i + j + 1 != k) continue;

				int greats = C[cur_great_than][j];
				int lesss = C[cur_less_than][i];

				long long ret = greats;
				ret = (ret * lesss) % MOD;
				ret = (ret * fact[k]) % MOD;

				ret = (ret * solve(cur_less_than - i, cur_great_than - j, i, 1)) % MOD;
				lol = (lol + ret) % MOD;
			}

		lol = (lol * mul) % MOD;

		// cout << pos << " " << idx << " " << lol << endl;
		res = (res + lol) % MOD;
	}

	// cout << res << " " << arr[pos] << endl;
	res = (res * arr[pos]) % MOD;
	res = (res * modpow(fact[same-1], MOD-2));

	return res;
}

void read() {
	cin >> n >> k;
	for(int i = 0 ; i < n ; i++)
		cin >> arr[i];
}

int work() {
	int ret = 0;
	for(int i = 0 ; i < n ; i++)
		ret = (ret + calc(i)) % MOD;
	return ret;
}

int main() {
	read();
	prepare();
	cout << work() << endl;
	return 0;
}