#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e5 + 5;
const int X = 11;

// 0: kurang dari z,
// 1: = z
// 2: lebih dari z

int temp[3][X];
int dp[N][3][X];

vector<int> adj[N];
int n, m, z, x;

void dfs(int now, int prv) {
    dp[now][0][0] = z - 1;
    dp[now][1][1] = 1;
    dp[now][2][0] = m - z;

    for(int nex : adj[now]) {
        if(nex == prv) continue;
        dfs(nex, now);

        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j <= x ; j++) {
                temp[i][j] = dp[now][i][j];
                dp[now][i][j] = 0;
            }

        for(int j = 0 ; j <= x ; j++) {
            for(int k = 0 ; k <= j ; k++) {
                int &ret = dp[now][0][j];

                ret = (ret + 1ll * temp[0][k] * dp[nex][0][j - k]) % MOD;
                ret = (ret + 1ll * temp[0][k] * dp[nex][1][j - k]) % MOD;
                ret = (ret + 1ll * temp[0][k] * dp[nex][2][j - k]) % MOD;

                int &cur = dp[now][1][j];
                cur = (cur + 1ll * temp[1][k] * dp[nex][0][j - k]) % MOD;

                int &wut = dp[now][2][j];
                wut = (wut + 1ll * temp[2][k] * dp[nex][0][j - k]) % MOD;
                wut = (wut + 1ll * temp[2][k] * dp[nex][2][j - k]) % MOD;
            }
        }
    }
}

void read() {
    scanf("%d %d", &n, &m);

    for(int i = 1 ; i < n ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    scanf("%d %d", &z, &x);
}

int main() {
    read();
    dfs(1, 0);

    int ret = 0;
    for(int i = 0 ; i < 3 ; i++)
        for(int j = 0 ; j <= x ; j++) {
            ret = (ret + dp[1][i][j]) % MOD;
        }

    printf("%d\n", ret);
    return 0;
}