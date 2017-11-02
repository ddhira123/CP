#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 5;
const int LOG = 30;

vector<pair<int ,int>> adj[N];

bool vis[N][2];
vector<int> seen;

int n, m;

void dfs(int now, int parity, int bit) {
    if(vis[now][parity]) {
        return;
    }

    vis[now][parity] = true;
    if(!vis[now][parity ^ 1]) {
        seen.push_back(now);
    }

    for(pair<int, int> nex: adj[now]) {
        int cost = nex.second & (1 << bit);
        cost = (cost > 0);

        dfs(nex.first, parity ^ cost, bit);
    }
}

long long solve_component(int now, int bit) {
    seen.clear();
    dfs(now, 0, bit);

    int one = 0;
    int zero = 0;
    int both = 0;
    long long ret = 0;

    for(int x : seen) {
        if(vis[x][0] && vis[x][1]) {
            ret += (zero + one + both);
            both++;
        } else if(vis[x][0]) {
            ret += (one + both);
            zero++;
        } else {
            ret += (zero + both);
            one++;
        }
    }

    ret *= (1ll << bit);
    return ret;
}

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0 ; i < m ; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
}

long long solve() {
    long long ret = 0;

    for(int bit = 0 ; bit < LOG ; bit++) {
        memset(vis, false, sizeof vis);

        for(int i = 1 ; i <= n ; i++)
            if(!vis[i][0] && !vis[i][1]) {
                ret += solve_component(i, bit);
            }
    }

    return ret;
}

void reset() {
    for(int i = 0 ; i < N ; i++) {
        adj[i].clear();
    }
}

int main() {
    int t;
    scanf("%d", &t);

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        cout << solve() << "\n";
        reset();
    }
    return 0;
}
