#include <bits/stdc++.h>
using namespace std;

const int N = 20005;
const int K = 50005;
const double EPS = 1e-9;

double dp[K];
long long psum[N];

int arr[N];
int n, k;

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &arr[i]);
    }
}

double work() {
    sort(arr + 1, arr + n + 1);
    reverse(arr + 1, arr + n + 1);

    for(int i = 1 ; i <= n ; i++) {
        psum[i] = psum[i-1] + arr[i];
    }

    dp[0] = (double)psum[n] / n;
    for(int i = 1 ; i <= k ; i++) {
        int lo = 1, hi = n;

        while(lo < hi) {
            int mid = (lo + hi + 1) / 2;

            if(arr[mid] + EPS > dp[i-1]) {
                // printf("%d arr %d dp %.9lf\n", mid, arr[mid], dp[i-1]);
                lo = mid;
            } else {
                hi = mid-1;
            }
        }

        // printf("i %d lo %d\n",i, lo);

        dp[i] = psum[lo];
        dp[i] += dp[i-1] * (n - lo);
        dp[i] /= n;
    }

    return dp[k];
}

int main() {
    int t; cin >> t;

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        printf("Case #%d: %.9lf\n", tc, work());
    }
    return 0;
}