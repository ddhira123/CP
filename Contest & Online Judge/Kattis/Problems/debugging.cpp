#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

long long dp[N];
int n, r, p;

long long solve(int x) {
    long long &ret = dp[x];
    if(ret != -1) {
        return ret;
    }

    ret = 4e18;
    int cur = 1;

    while((x + cur) / (cur + 1) != 1) {
        int max_part = (x + cur) / (cur + 1);
        ret = min(ret, solve(max_part) + r + 1ll * p * cur);

        int lo = cur, hi = x - 1;

        while(lo < hi) {
            int mid = (lo + hi + 1) / 2;

            if(max_part == (x + mid) / (mid + 1)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }

        cur = lo + 1;
    }

    ret = min(ret, solve(1) + r + 1ll * p * cur);

    return ret;
}

int main() {
    memset(dp, -1, sizeof dp);
    dp[1] = 0;

    cin >> n >> r >> p;

    cout << solve(n) << endl;
    return 0;
}