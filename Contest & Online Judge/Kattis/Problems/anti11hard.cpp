#include <bits/stdc++.h>
using namespace std;

const int N = 10005;
const int S = 15;
const int MOD = 1e9 + 7;

int nxt[S][2];
int n;
string str;
int dp[N][S];

int solve(int sisa, int now) {
    if(sisa == 0) {
        return now != str.length();
    }

    int &ret = dp[sisa][now];
    if(ret != -1) {
        return ret;
    }

    ret = (solve(sisa-1, nxt[now][0]) + solve(sisa-1, nxt[now][1])) % MOD;
    return ret;
}

void prepare() {
    memset(dp, -1, sizeof dp);

    int cur = str[0] - '0';
    int fail = 0;

    nxt[0][cur] = 1;
    nxt[0][1-cur] = 0;

    for(int i = 1 ; i < str.length() ; i++) {
        cur = str[i] - '0';

        nxt[i][cur] = i+1;
        nxt[i][1-cur] = nxt[fail][1-cur];

        fail = nxt[fail][cur];
    }

    nxt[str.length()][0] = nxt[str.length()][1] = str.length();
}

int main() {
    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        cin >> n >> str;
        prepare();
        cout << solve(n, 0) << endl;
    }
    return 0;
}