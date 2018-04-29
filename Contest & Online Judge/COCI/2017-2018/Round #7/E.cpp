#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const int M = 505;

int dp[N][M][3];
int temp[M][3];

int arr[N];
vector<int> adj[N];
int n, m;

void solve(int now, int nex) {
    for(int i = 0 ; i <= m ; i++) {
        temp[i][0] = dp[now][i][0];
        temp[i][1] = dp[now][i][1];
        temp[i][2] = dp[now][i][2];
    }

    for(int i = 0 ; i <= m ; i++) {
        if(temp[i][0] != -1) {
            for(int j = 0 ; i + j + 1 <= m ; j++) {
                // pake 1
                if(dp[nex][j][1] != -1) {
                    dp[now][i + j + 1][0] = max(dp[now][i + j + 1][0], temp[i][0] + dp[nex][j][1]);
                }

                // pake 0
                if(dp[nex][j][0] != -1) {
                    dp[now][i + j + 1][2] = max(dp[now][i + j + 1][2], temp[i][0] + dp[nex][j][0]);
                }

                // pake 2
                if(dp[nex][j][2] != -1) {
                    dp[now][i + j + 1][2] = max(dp[now][i + j + 1][2], temp[i][0] + dp[nex][j][2]);
                }
            }
        }

        if(temp[i][1] != -1) {
            for(int j = 0 ; i + j + 1 <= m ; j++) {
                if(dp[nex][j][1] != -1) {
                    dp[now][i + j + 1][1] = max(dp[now][i + j + 1][1], temp[i][1] + dp[nex][j][1]);
                }
            }
        }

        if(temp[i][2] != -1) {
            for(int j = 0 ; i + j + 1 <= m ; j++) {
                if(dp[nex][j][1] != -1) {
                    dp[now][i + j + 1][2] = max(dp[now][i + j + 1][2], temp[i][2] + dp[nex][j][1]);
                }
            }
        }
    }
}

void dfs(int now, int prv) {
    dp[now][0][0] = 0;
    dp[now][1][0] = arr[now];

    dp[now][1][1] = 0;
    dp[now][2][1] = arr[now];

    dp[now][0][2] = 0;
    dp[now][1][2] = arr[now];

    for(int nex : adj[now]) {
        if(nex == prv) continue;
        dfs(nex, now);
        solve(now, nex);
    }
}

void read() {
    cin >> n >> m;

    for(int i = 1 ; i <= n ; i++) {
        cin >> arr[i];
    }

    for(int i = 1 ; i < n ; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void prepare() {
    memset(dp, -1, sizeof dp);
}

int work() {
    prepare();
    dfs(1, 0);

    int ret = 0;
    for(int i = 0 ; i <= m ; i++) {
        ret = max(ret, dp[1][i][0]);
        ret = max(ret, dp[1][i][1]);
        ret = max(ret, dp[1][i][2]);
    }

    return ret;
}

int main() {
    read();
    prepare();
    cout << work() << endl;
    return 0;
}