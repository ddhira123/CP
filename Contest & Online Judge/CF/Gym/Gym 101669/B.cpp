#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 5;
const int MOD = 1e9 + 7;

int sumDP[3 * MAXN];
int dp[MAXN];
int psum[MAXN];

int n, m;

void read() {
    scanf("%d %d", &n, &m);
    for (int i = 0 ; i < m ; i++) {
        int x; scanf("%d", &x);
        psum[x]++;
    }
}

int work() {
    for (int i = 1 ; i <= n+2 ; i++)
        psum[i] += psum[i-1];
    dp[n+1] = 1;
    dp[n+2] = 1;

    int lastOne = n;
    for (int i = n ; i >= 1 ; i--) {
        int cnt = psum[i] - psum[i-1];
        if (cnt == 0) {
            dp[i] = dp[i+1];
        } else {
            while (lastOne >= i) {
                int sel = psum[lastOne] - lastOne + MAXN;
                int cntOne = psum[lastOne+1] - psum[lastOne];

                if (cntOne == 0) {
                    sumDP[sel] = (sumDP[sel] + dp[lastOne+2]) % MOD;
                }

                lastOne--;
            }
        }

        int sel = psum[i-1] - (i-1) + MAXN;
        dp[i] = (dp[i] + sumDP[sel]) % MOD;

        // cout << i << " " << dp[i] << endl;
    }

    return dp[1];
}

int main() {
    read();
    printf("%d\n", work());
    return 0;
}