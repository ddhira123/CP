#include <bits/stdc++.h>
using namespace std;

const int N = 42;

int dp[N][N][N][N];
int mins[N][N][N][N];
int arr[N][N];
int n, m;

void read() {
    cin >> n >> m;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < m ; j++)
            cin >> arr[i][j];
}

int get_mins(int r_top, int c_top, int r_bot, int c_bot) {
    if(r_top > r_bot || c_top > c_bot) return 1e9;

    int &ret = mins[r_top][c_top][r_bot][c_bot];
    if(ret != -1) {
        return ret;
    }

    ret = arr[r_top][c_top];

    ret = min(ret, get_mins(r_top+1, c_top, r_bot, c_bot));
    ret = min(ret, get_mins(r_top, c_top+1, r_bot, c_bot));

    return ret;
}

int solve(int r_top, int c_top, int r_bot, int c_bot) {
    int &ret = dp[r_top][c_top][r_bot][c_bot];
    if(ret != -1) {
        return ret;
    }

    ret = 0;
    for(int i = r_top ; i < r_bot ; i++) {
        ret = max(ret, solve(r_top, c_top, i, c_bot) + solve(i+1, c_top, r_bot, c_bot));
    }
    for(int i = c_top ; i < c_bot ; i++) {
        ret = max(ret, solve(r_top, c_top, r_bot, i) + solve(r_top, i+1, r_bot, c_bot));
    }

    // printf("%d %d %d %d -> %d + %d\n", r_top, c_top, r_bot, c_bot, ret, get_mins(r_top, c_top, r_bot, c_bot));
    if(r_top != r_bot || c_top != c_bot)
        ret += get_mins(r_top, c_top, r_bot, c_bot);

    return ret;
}

int work() {
    memset(dp, -1, sizeof dp);
    memset(mins, -1, sizeof mins);

    return solve(0, 0, n-1, m-1);
}

int main() {
    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        printf("Case #%d: %d\n", tc, work());
    }
    return 0;
}