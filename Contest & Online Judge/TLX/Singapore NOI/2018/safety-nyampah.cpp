#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
const int MX = 5005;

int dp[MX][MX];

int arr[MX];
int n, h;

int mx = 0;

void read() {
    scanf("%d %d", &n, &h);

    mx = 0;
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
        mx = max(mx, arr[i]);
    }

    h = min(h, mx);
}

long long solve_zero() {
    sort(arr, arr + n);

    long long ret = 0;
    for(int i = 0 ; i < n ; i++) {
        ret += abs(arr[i] - arr[n / 2]);
    }

    return ret;
}

long long brute_rec(int dir, int cur, int height) {
    if(height < 0) return 4e18;
    if(cur < 0 || cur == n) return 0;

    long long ret = 4e18;

    for(int i = -h ; i <= h ; i++) {
        ret = min(ret, brute_rec(dir, cur + dir, height + i));
    }
    ret += abs(height - arr[cur]);

    return ret;
}

long long brute() {
    long long ret = 4e18;

    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j <= 0 ; j++) {
            int cur = j + arr[i];

            long long temp = brute_rec(-1, i, cur);
            temp += brute_rec(1, i, cur);
            temp -= abs(cur - arr[i]);

            ret = min(ret, temp);
        }
    }

    return ret;
}

long long work() {
    if(h == 0) {
        return solve_zero();
    }
    if(n <= 10 && h <= 2) {
        return brute();
    }

    for(int i = 0 ; i <= mx ; i++) {
        dp[n-1][i] = abs(i - arr[n-1]);
    }

    for(int i = n-2 ; i >= 0 ; i--) {
        deque<pair<int, int>> dq;

        for(int j = 0 ; j <= h ; j++) {
            while(!dq.empty() && dq.back().second >= dp[i+1][j]) {
                dq.pop_back();
            }

            dq.push_back({j, dp[i+1][j]});
        }

        for(int j = 0 ; j <= mx ; j++) {
            if(j + h <= mx) {
                while(!dq.empty() && dq.back().second >= dp[i+1][j+h]) {
                    dq.pop_back();
                }

                dq.push_back({j + h, dp[i+1][j+h]});
            }

            while(!dq.empty() && dq.front().first < j - h) {
                dq.pop_front();
            }

            dp[i][j] = abs(j - arr[i]) + dq.front().second;
        }
    }

    int ret = 1e9;
    for(int i = 0 ; i <= mx ; i++) {
        ret = min(ret, dp[0][i]);
    }

    return ret;
}

int main() {
    read();
    printf("%lld\n", work());
    return 0;
}