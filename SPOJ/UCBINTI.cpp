#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int dp[N][2];
int arr[N];
int cnt[N][2];
int n,k;

int main(){
	ios_base::sync_with_stdio(0);
	cin >> n >> k;
	for(int i = 0 ; i < n ; i++){
		cin >> arr[i];
		arr[i] &= 1;
	}
	for(int i = 0 ; i < k ; i++)
		for(int j = i ; j < n ; j += k)
			cnt[i][arr[j]]++;
	dp[0][1] = (int)1e9;		
	for(int i = 0 ; i < k ; i++){
		dp[i + 1][0] = dp[i + 1][1] = (int)1e9;
		//cout << i << " " << cnt[i][0] << " " << cnt[i][1] << endl;
		//cout << dp[i][0] << " " << dp[i][1] << endl;
		for(int j = 0 ; j < 2 ; j++)
			for(int use = 0 ; use < 2 ; use++)
				dp[i + 1][j ^ use] = min(dp[i + 1][j ^ use],dp[i][j] + cnt[i][use ^ 1]);
	}		
	cout << dp[k][0] << endl;
	return 0;
}
