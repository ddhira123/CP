#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;
const int MOD = 1e9 + 7;

int dp[N][N][2];

int step[N];
string s;
int k;

void precompute() {
    step[1] = 0;
    for(int i = 2 ; i < N ; i++) {
        step[i] = 1 + step[__builtin_popcount(i)];
    }
}

int solve(int pos, int use, int kurang) {
    if(pos == -1) {
        if(use > 0) {
            return 1 + step[use] == k;
        } else {
            return 0;
        }
    } else {
        int &ret = dp[pos][use][kurang];

        if(ret != -1) {
            return ret;
        }

        ret = 0;
        if(kurang) {
            for(int i = 0 ; i < 2 ; i++) {
                ret += solve(pos-1, use + i, kurang); 
            }
        } else {
            for(int i = 0 ; i <= s[pos] - '0' ; i++) {
                ret += solve(pos-1, use + i, i < s[pos] - '0');
            }
        }

        ret %= MOD;
        return ret;
    }
}

int main() {
    cin >> s >> k;
    reverse(s.begin(), s.end());

    precompute();
    memset(dp, -1, sizeof dp);

    int len = s.length();
    int ret = solve(len-1, 0, 0);

    if(k == 0) {
        ret = 1;
    }
    if(k == 1) {
        ret--;
    }

    cout << ret << endl;
    return 0;
}