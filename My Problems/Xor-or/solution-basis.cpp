#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 5;
const int LOG = 30;

vector<pair<int, int>> adj[N];
bool vis[N];
int xor_sum[N];

vector<int> cycle;
vector<int> seen;

int n, m;

void dfs(int now) {
    vis[now] = true;
    seen.push_back(now);

    for(pair<int, int> nex : adj[now]) {
        if(vis[nex.first]) {
            cycle.push_back(xor_sum[now] ^ xor_sum[nex.first] ^ nex.second);
        } else {
            xor_sum[nex.first] = xor_sum[now] ^ nex.second;
            dfs(nex.first);
        }
    }
}

long long solve_component(int now) {
    seen.clear();
    cycle.clear();

    xor_sum[now] = 0;
    dfs(now);

    long long ret = 0;
    int cycle_or = 0;

    for(int x : cycle) {
        cycle_or |= x;
    }

    for(int i = 0 ; i < LOG ; i++)
        if(cycle_or & (1 << i)) {
            ret += (1ll << i) * seen.size() * (seen.size() - 1) / 2;
        } else {
            int active = 0;
            for(int node : seen)
                active += ((xor_sum[node] & (1 << i)) > 0);
            ret += (1ll << i) * active * (seen.size() - active);
        }

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

    for(int i = 1 ; i <= n ; i++) {
        if(!vis[i]) {
            ret += solve_component(i);
        }
    }

    return ret;
}

void reset() {
    for(int i = 0 ; i < N ; i++) {
        adj[i].clear();
        vis[i] = false;
    }
}

int main() {
    int t;
    scanf("%d", &t);

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        printf("%lld\n", solve());
        reset();
    }
    return 0;
}
