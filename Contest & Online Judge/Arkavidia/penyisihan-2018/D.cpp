#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

long long dp[N];
int arr[N];
int n, k;

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &arr[i]);
    }
}

long long solve() {
    sort(arr + 1, arr + n + 1);

    for(int i = 1 ; i < k ; i++) {
        dp[i] = 1e18;
    }

    long long best = -arr[1];

    for(int i = k ; i <= n ; i++) {
        best = min(best, dp[i-k] - arr[i-k+1]);
        dp[i] = best + arr[i];
    }

    return dp[n];
}

int main() {
    int t; scanf("%d", &t);

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        printf("%lld\n", solve());
    }
    return 0;
}