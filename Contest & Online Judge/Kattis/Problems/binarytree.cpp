#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MOD = 21092013;

string read_string() {
    static char s[N];
    scanf("%s", s);
    return (string)s;
}

string s, t;

vector<char> stek;
int nex[N][2];
int dp[N];

int solve(int now) {
    if(now == -1) return 0;
    now++;

    int &ret = dp[now];
    if(ret != -1) return ret;

    ret = 1 + solve(nex[now][0]) + solve(nex[now][1]);
    ret %= MOD;

    return ret;
}

void read() {
    s = read_string();
    t = read_string();
}

void prepare() {
    stek.clear();

    for(char x : s) {
        if(x == 'U') {
            if(!stek.empty()) {
                stek.pop_back();
            }
        } else {
            stek.push_back(x);
        }
    }

    int len = t.length();
    nex[len][0] = nex[len][1] = -1;

    for(int i = len-1 ; i >= 0 ; i--) {
        nex[i][0] = nex[i+1][0];
        nex[i][1] = nex[i+1][1];

        if(t[i] == 'L') nex[i][0] = i;
        if(t[i] == 'R') nex[i][1] = i;
    }

    memset(dp, -1, sizeof dp);
}

int work() {
    int sz = stek.size();
    int ret = solve(nex[0][0]) + solve(nex[0][1]) + 1;
    ret %= MOD;

    for(int i = 0 ; i < t.length() && sz > 0 ; i++) {
        if(t[i] == 'U') {
            sz--;

            if(stek[sz] == 'L') ret = (ret + solve(nex[i][1]) + 1) % MOD;
            else                ret = (ret + solve(nex[i][0]) + 1) % MOD;
        }
    }

    return ret;
}

int main() {
    int t; cin >> t;

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        prepare();
        printf("Case %d: %d\n", tc, work());
    }
    return 0;
}