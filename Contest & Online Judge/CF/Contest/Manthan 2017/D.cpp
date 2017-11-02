#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int LG = 17;

int anc[N][LG];
int sum[N][LG];
int depth[N];

vector<pair<int, int>> chld[N];
int parent[N], type[N];

int n;

void build(int now, int par, int val) {
    anc[now][0] = par;
    sum[now][0] = val;
    depth[now] = depth[par] + 1;

    for(int i = 1 ; (1 << i) <= depth[now] ; i++) {
        int par = anc[now][i - 1];
        int cur_sum = sum[now][i - 1] + sum[par][i - 1];

        anc[now][i] = anc[par][i-1];
        sum[now][i] = cur_sum;
    }
}

void dfs(int now) {
    for(pair<int, int> nex : chld[now]) {
        build(nex.first, now, nex.second);

        dfs(nex.first);
    }
}

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d %d", parent + i, type + i);
    }
}

void init() {
    for(int i = 1 ; i <= n ; i++) {
        if(parent[i] != -1) {
            chld[parent[i]].push_back({i, type[i]});
        }
    }

    for(int i = 1 ; i <= n ; i++)
        if(parent[i] == -1) {
            dfs(i);
        }
}

int get_lca(int u, int v) {
    if(depth[v] > depth[u]) {
        swap(u, v);
    }

    int diff = depth[u] - depth[v];

    for(int i = 0 ; diff ; i++)
        if(diff & (1 << i)) {
            u = anc[u][i];
            diff -= (1 << i);
        }

    if(u == v) {
        return u;
    }

    for(int i = LG-1 ; i >= 0 ; i--) {
        if(depth[u] >= (1 << i) && anc[u][i] != anc[v][i]) {
            u = anc[u][i];
            v = anc[v][i];
        }
    }

    if(depth[u] == 0 || anc[u][0] != anc[v][0]) {
        return -1;
    }

    return anc[u][0];
}

int get_sum(int now, int up) {
    int ret = 0;
    for(int i = LG - 1 ; i >= 0 ; i--)
        if(up & (1 << i)) {
            ret += sum[now][i];
            now = anc[now][i];
            up -= (1 << i);
        }
    return ret;
}

bool is_special(int u, int v) {
    if(u == v) {
        return false;
    }

    int lca = get_lca(u, v);
    if(lca != u) {
        return false;
    }

    int up = depth[v] - depth[lca];
    if(get_sum(v, up) != 0) {
        return false;
    }

    return true;
}

bool is_part(int u, int v) {
    if(u == v) {
        return false;
    }

    int lca = get_lca(u, v);
    if(lca == -1) {
        return false;
    }
    if(lca == v) {
        return false;
    }

    int up = depth[v] - depth[lca];
    if(get_sum(v, up) != up) {
        return false;
    }

    up = depth[u] - depth[lca];
    if(get_sum(u, up) != 0) {
        return false;
    }

    return true;
}

void work() {
    int q;
    scanf("%d", &q);

    for(int i = 0 ; i < q ; i++) {
        int t, u, v;
        scanf("%d %d %d", &t, &u, &v);

        bool ret;
        if(t == 1)  ret = is_special(u, v);
        else        ret = is_part(u, v);

        printf("%s\n", ret ? "YES" : "NO");
    }
}

int main() {
    read();
    init();
    work();
    return 0;
}