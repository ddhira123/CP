#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

int dp[N];
int arr[N];
int n, m;

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
    }
}

bool test(int x) {
    for(int i = n-1 ; i >= 0 ; i--) {
        dp[i] = n-i-1;

        for(int j = i+1 ; j < n ; j++) {
            int bebas = j - i;
            int jarak = abs(arr[j] - arr[i]);

            if(jarak <= 1ll * x * bebas) {
                dp[i] = min(dp[i], bebas-1 + dp[j]);
            }
        }
    }

    int mins = n-1;
    for(int i = 0 ; i < n ; i++) {
        // printf("x %d i %d dp[] %d\n", x, i, dp[i] + i);
        mins = min(mins, dp[i] + i);
    }

    // cout << x << " " << mins << endl;

    return mins <= m;
}

int solve() {
    long long lo = 0;
    long long hi = 2e9;

    while(lo < hi) {
        int mid = (lo + hi) / 2;
        if(test(mid)) {
            hi = mid;
        } else {
            lo = mid+1;
        }
    }

    return lo;
}

int main() {
    read();
    cout << solve() << endl;
    return 0;
}