#include <bits/stdc++.h>
using namespace std;

const int N = 31;
const int INF = 1e9;

int dp[N][N][N*N];
vector<int> shoots;

int d;
string s;

int solve(int charge, int shoot, int swaps) {
    if(swaps < 0) return INF;
    if(charge + shoot == s.length()) {
        if(shoot != shoots.size()) {
            return INF;
        }
        return 0;
    }

    int &ret = dp[charge][shoot][swaps];
    if(ret != -1) {
        return ret;
    }

    ret = solve(charge+1, shoot, swaps);
    if(shoot < shoots.size()) {
        int nswaps = swaps - abs(charge + shoot - shoots[shoot]);
        ret = min(ret, (1 << charge) + solve(charge, shoot+1, nswaps));
    }

    return ret;
}

void read() {
    cin >> d >> s;
}

void prepare() {
    memset(dp, -1, sizeof dp);
    shoots.clear();

    for(int i = 0 ; i < s.length() ; i++) {
        if(s[i] == 'S') {
            shoots.push_back(i);
        }
    }
}

int work() {
    for(int i = 0 ; i < N * N ; i++) {
        if(solve(0, 0, i) <= d) {
            return i;
        }
    }
    return -1;
}

int main() {
    int t; cin >> t;

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        prepare();
        int ret = work();

        if(ret == -1) {
            printf("Case #%d: IMPOSSIBLE\n", tc);
        } else {
            printf("Case #%d: %d\n", tc, ret);
        }
    }
    return 0;
}