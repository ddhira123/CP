#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
const int MOD = 1e9 + 7;

int arr[N];
int dp[N];
int n, k;
map<int,int> cnt;
int active;

void read() {
	scanf("%d %d", &n, &k);
	for(int i = 1 ; i <= n ; i++)
		scanf("%d", &arr[i]);
}

int get(int l, int r) {
	int ret = dp[r];
	if(l > 0) ret -= dp[l-1];
	if(ret < 0) ret += MOD;
	return ret;
}

int solve() {
	int l = 1;
	dp[0] = 1;

	for(int r = 1 ; r <= n ; r++) {
		cnt[arr[r]]++;
		if(arr[r] <= k && cnt[arr[r]] == 1) {
			active++;
		}
		while(active == k+1) {
			cnt[arr[l]]--;
			if(arr[l] <= k && cnt[arr[l]] == 0) {
				active--;
			}
			l++;
		}

		dp[r] = get(l-1, r-1);
		// printf("%d -> %d\n", r, dp[r]);
		dp[r] += dp[r-1];
		dp[r] %= MOD;
	}

	int ret = dp[n] - dp[n-1];
	if(ret < 0) ret += MOD;
	return ret;
}

int main() {
	read();
	printf("%d\n", solve());
	return 0;
}