#include <bits/stdc++.h>
using namespace std;

const int MAX_LENGTH = 10;
const int N = 55;
const int K = 26;
const int MOD = 1e9 + 7;

int dp[N][1 << MAX_LENGTH];
string s;
int ways[N];
int next_mask[1 << MAX_LENGTH][K][K];
int n, k;

void make_ways() {
    ways[0] = 1;
    for(int i = 1 ; i < N ; i++) {
        ways[i] = 1ll * ways[i-1] * k * k % MOD;
    }
}

void make_next_mask() {
    for(int i = 1 ; i < (1 << s.length()) ; i++) {
        for(int a = 0 ; a < k ; a++)
            for(int b = 0 ; b < k ; b++) {
                int ret = 1;

                for(int j = 0 ; j < s.length() ; j++)
                    if(i & (1 << j)) {
                        int cur = j;

                        if(s[cur] == a+'a') {
                            ret |= (1 << (cur+1));
                            if(cur+1 < s.length() && s[cur+1] == b+'a') {
                                ret |= (1 << (cur+2));
                            }
                        }

                        if(s[cur] == b+'a') {
                            ret |= (1 << (cur+1));
                            if(cur+1 < s.length() && s[cur+1] == a+'a') {
                                ret |= (1 << (cur+2));
                            }
                        }
                    }

                // printf("%d %d %d -> %d\n", i, a, b, ret);
                next_mask[i][a][b] = ret;
            }
    }
}

int solve(int sisa, int mask) {
    if(sisa == 0) return 0;

    int &ret = dp[sisa][mask];
    if(ret != -1) {
        return ret;
    }

    ret = 0;
    for(int i = 0 ; i < k ; i++)
        for(int j = 0 ; j < k ; j++) {
            int nex = next_mask[mask][i][j];

            if(nex & (1 << s.length())) {
                ret = (ret + ways[sisa-1]) % MOD;
            } else {
                ret = (ret + solve(sisa-1, nex)) % MOD;
            }
        }

    return ret;
}

void read() {
    cin >> s >> n >> k;
}

void prepare() {
    make_ways();
    make_next_mask();
    memset(dp, -1, sizeof dp);
}

int work() {
    return solve(n, 1);
}

int main() {
    int t; cin >> t;

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        prepare();
        cout << work() << endl;
    }
    return 0;
}