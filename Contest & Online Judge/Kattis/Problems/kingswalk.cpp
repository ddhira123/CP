#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
const int MOD = 5318008;

int stamp[N][N];
int dp[N][N];

int tgt;
int cur_t;

int n, r1, c1, r2, c2;

int solve(int sisa, int r) {
    if(r == 0 || r == n+1 || abs(tgt-r) > sisa) return 0;
    if(abs(tgt-r) == sisa) return 1;
    if(stamp[sisa][r] == cur_t) return dp[sisa][r];

    stamp[sisa][r] = cur_t;
    dp[sisa][r] = solve(sisa-1, r) + solve(sisa-1, r-1) + solve(sisa-1, r+1);
    dp[sisa][r] %= MOD;

    return dp[sisa][r];
}

int main() {
    int t; cin >> t;
    for(cur_t = 1 ; cur_t <= t ; cur_t++) {
        cin >> n >> r1 >> c1 >> r2 >> c2;

        int ret = 0;
        if(abs(r1-r2) >= abs(c1-c2)) {
            tgt = c2;
            ret = solve(abs(r1-r2), c1);
        } else {
            tgt = r2;
            ret = solve(abs(c1-c2), r1);
        }

        cout << ret << endl;
    }
    return 0;
}