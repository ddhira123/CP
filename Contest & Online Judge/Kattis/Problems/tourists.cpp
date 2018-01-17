#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int LOG = 18;

vector<int> adj[N];
int depth[N];
int anc[N][LOG];

int n;

void build(int now, int prv) {
    anc[now][0] = prv;
    depth[now] = depth[prv] + 1;

    for(int i = 1 ; (1 << i) <= depth[now] ; i++) {
        anc[now][i] = anc[anc[now][i-1]][i-1];
    }
}

void dfs(int now, int prv) {
    for(int nex : adj[now]) {
        if(nex == prv) continue;
        build(nex, now);
        dfs(nex, now);
    }
}

int get_lca(int u, int v) {
    if(depth[u] < depth[v]) swap(u, v);

    int diff = depth[u] - depth[v];
    for(int i = 0 ; diff ; i++) {
        if(diff & (1 << i)) {
            diff -= (1 << i);
            u = anc[u][i];
        }
    }

    if(u == v) {
        return u;
    }

    for(int i = LOG-1 ; i >= 0 ; i--) {
        if(depth[u] >= (1 << i) && anc[u][i] != anc[v][i]) {
            u = anc[u][i];
            v = anc[v][i];
        }
    }

    return anc[u][0];
}

int get_dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
}

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i < n ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void prepare() {
    dfs(1, 0);
}

long long work() {
    long long ret = 0;

    for(int i = 1 ; i <= n ; i++)
        for(int j = i+i ; j <= n ; j += i) {
            ret += get_dist(i, j) + 1;
        }

    return ret;
}

int main() {
    read();
    prepare();
    cout << work() << endl;
    return 0;
}