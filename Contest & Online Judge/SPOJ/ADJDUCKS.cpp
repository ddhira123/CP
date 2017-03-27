#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

long long arr[N];
long long dp[N];
int n;

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 0 ; i < n ; i++)
        cin >> arr[i];
    sort(arr,arr + n);
    dp[n - 1] = (long long)4e18;
    dp[n - 2] = arr[n - 1] - arr[n - 2];
    for(int i = n - 3 ; i >= 0 ; i--) {
        dp[i] = dp[i + 2] + arr[i + 1] - arr[i];
        dp[i] = min(dp[i],dp[i + 3] + arr[i + 2] - arr[i]);
    }
    cout << dp[0] << endl;
    return 0;
}
