#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

vector<int> adj[N];
int dp[N][2];
bool is_important[N];

int n, k;

void dfs(int now, int prv) {
    dp[now][is_important[now]] = 1;

    for(int nex : adj[now]) {
        if(nex == prv) continue;
        dfs(nex, now);

        int tmp[2];
        tmp[0] = dp[now][0];
        tmp[1] = dp[now][1];

        // pake lanjut
        dp[now][0] = 1ll * tmp[0] * dp[nex][0] % MOD;
        dp[now][1] = 1ll * tmp[0] * dp[nex][1] % MOD;
        dp[now][1] = (dp[now][1] + 1ll * tmp[1] * dp[nex][1]) % MOD;
        dp[now][1] = (dp[now][1] + 1ll * tmp[1] * dp[nex][0]) % MOD;

        // skip
        dp[now][0] = (dp[now][0] + tmp[0]) % MOD;
        dp[now][1] = (dp[now][1] + tmp[1]) % MOD;
    }
}

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 1 ; i < n ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 0 ; i < k ; i++) {
        int x; scanf("%d", &x);
        is_important[x] = 1;
    }
}

void work() {
    dfs(1, 0);

    int ret = 0;
    for(int i = 1 ; i <= n ; i++) {
        ret = (ret + dp[i][1]) % MOD;
    }

    cout << ret << endl;
}

int main() {
    read();
    work();
    return 0;
}