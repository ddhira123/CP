#include <bits/stdc++.h>
using namespace std;

const int N = 705;
const int MOD = 1e9 + 7;

string s;
int dp[N][N][2][2];
int cur;

int solve(int sisa, int lebih, int same, int exist) {
    if(lebih < 0) return 0;

    if(sisa < 0) {
        return (lebih == 0) && (exist);
    }

    int &ret = dp[sisa][lebih][same][exist];
    if(ret != -1) return ret;

    ret = 0;
    if(same) {
        for(int i = 0 ; i <= s[sisa] - '0' ; i++) {
            int nsame = i == (s[sisa] - '0');
            int nexist = exist || (cur == i);

            if(i == cur) {
                if(exist) {
                    ret = (ret + solve(sisa-1, lebih-1, nsame, 1)) % MOD;
                } else {
                    ret = (ret + solve(sisa-1, lebih, nsame, 0)) % MOD;
                    ret = (ret + solve(sisa-1, lebih, nsame, 1)) % MOD;
                }
            } else {
                ret = (ret + solve(sisa-1, lebih - ((i != 0) && i > cur), nsame, nexist)) % MOD;
            }
        }
    } else {
        for(int i = 0 ; i < 10 ; i++) {
            int nsame = false;
            int nexist = exist || (cur == i);

            if(i == cur) {
                if(exist) {
                    ret = (ret + solve(sisa-1, lebih-1, nsame, 1)) % MOD;
                } else {
                    ret = (ret + solve(sisa-1, lebih, nsame, 0)) % MOD;
                    ret = (ret + solve(sisa-1, lebih, nsame, 1)) % MOD;
                }
            } else {
                ret = (ret + solve(sisa-1, lebih - ((i != 0) && i > cur), nsame, nexist)) % MOD;
            }
        }
    }

    return ret;
}

int work() {
    reverse(s.begin(), s.end());
    int ret = 0;

    for(cur = 1 ; cur <= 9 ; cur++) {
        memset(dp, -1, sizeof dp);

        int val = 0;

        for(int len = 1 ; len < s.length() ; len++) {
            int ten = 1;

            for(int pos = 0 ; pos < len ; pos++) {
                int tmp = 0;
                for(int i = 1 ; i <= 9 ; i++) {
                    if(i == cur) {
                        tmp = (tmp + solve(len-2, pos, false, 0)) % MOD;
                        tmp = (tmp + solve(len-2, pos, false, 1)) % MOD;
                    } else {
                        tmp = (tmp + solve(len-2, pos - ((i != 0) && (i > cur)), false, 0)) % MOD;
                    }
                }
                tmp = 1ll * ten * tmp % MOD;
                tmp = 1ll * cur * tmp % MOD;

                val = (val + tmp) % MOD;

                ten = 10ll * ten % MOD;
            }
        }

        //cout << cur << " " << val << endl;
        ret = (ret + val) % MOD;

        val = 0;

        {
            int len = s.length();
            int ten = 1;
            int back = s[len-1];

            for(int pos = 0 ; pos < len ; pos++) {
                int tmp = 0;

                for(int i = 1 ; i <= back - '0' ; i++) {
                    int same = i == (back - '0');

                    if(i == cur) {
                        tmp = (tmp + solve(len-2, pos, same, 0)) % MOD;
                        tmp = (tmp + solve(len-2, pos, same, 1)) % MOD;
                    } else {
                        tmp = (tmp + solve(len-2, pos - ((i != 0) && (i > cur)), same, 0)) % MOD;
                    }
                }

                tmp = 1ll * ten * tmp % MOD;
                tmp = 1ll * cur * tmp % MOD;

                val = (val + tmp) % MOD;

                ten = 10ll * ten % MOD;
            }
        }

       // cout << val << endl;

        ret = (ret + val) % MOD;
    }

    return ret;
}

int main() {
    cin >> s;
    cout << work() << endl;
    return 0;
}

