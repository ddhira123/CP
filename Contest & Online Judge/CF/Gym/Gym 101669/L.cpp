#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int LOG = 18;

int anc[2][N][LOG];
int depth[2][N];

vector<int> adj[2][N];
// int psum[N];
int n;
int cnt[2][N];

void buildST(int mode, int now, int prv) {
    depth[mode][now] = depth[mode][prv]+1;
    anc[mode][now][0] = prv;

    for (int i = 1 ; (1 << i) <= depth[mode][now] ; i++) {
        anc[mode][now][i] = anc[mode][anc[mode][now][i-1]][i-1];
    }
}

void dfs(int mode, int now, int prv) {
    for (int nex : adj[mode][now]) {
        if (nex == prv) continue;
        buildST(mode, nex, now);
        dfs(mode, nex, now);
    }
}

int getLCA(int mode, int u, int v) {
    if (depth[mode][u] < depth[mode][v]) swap(u, v);
    int diff = depth[mode][u] - depth[mode][v];

    for (int i = 0 ; diff ; i++)
        if (diff & (1 << i)) {
            diff -= (1 << i);
            u = anc[mode][u][i];
        }

    if (u == v) return u;

    for (int i = LOG-1 ; i >= 0 ; i--)
        if (depth[mode][u] >= (1 << i) && anc[mode][u][i] != anc[mode][v][i]) {
            u = anc[mode][u][i];
            v = anc[mode][v][i];
        }

    return anc[mode][u][0];
}

void disable(int mode, int u, int v) {
    int lca = getLCA(mode, u, v);

    // psum[in[lca]]++;
    // psum[ot[lca]+1]--;

    // psum[in[lca]]--;
    // psum[in[lca]+1]++;
    // cnt[lca]++;
    cnt[mode][u]++;
    cnt[mode][v]++;
    cnt[mode][lca] -= 2;
    // cnt[anc[lca][0]]

    // printf("lca %d %d %d\n", lca, in[lca], ot[lca]);
}

void dfsProp(int mode, int now, int prv) {
    for (int nex : adj[mode][now]) {
        if (nex == prv) continue;
        dfsProp(mode, nex, now);
        cnt[mode][now] += cnt[mode][nex];
    }
}

void init() {
    scanf("%d", &n);
    for (int i = 1 ; i < n ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        adj[0][u].push_back(v);
        adj[0][v].push_back(u);
    }

    // dfs(1, -1);

    for (int i = 1 ; i < n ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        // disable(u, v);
        adj[1][u].push_back(v);
        adj[1][v].push_back(u);
    }
}

void prepare() {
    dfs(0, 1, -1);
    dfs(1, 1, -1);

    for (int mode = 0 ; mode < 2 ; mode++) {
        for (int i = 1 ; i <= n ; i++)
            for (int nex : adj[mode^1][i])
                if (nex > i) {
                    disable(mode, i, nex);
                }
    }

    dfsProp(0, 1, -1);
    dfsProp(1, 1, -1);
}

int minEdge = 1e9, ways;

void dfsSolve(int mode, int now, int prv) {
    for (int nex : adj[mode][now]) {
        if (nex == prv) continue;
        dfsSolve(mode, nex, now);

        int diffEdge = cnt[mode][nex];
        // printf("%d dari %d to %d\n", nex, in[nex]-1, in[nex]);
        // printf("sum %d %d\n", psum[in[nex]], psum[in[nex]-1]);

        int edge = 1 + diffEdge;

        if (edge < minEdge) {
            minEdge = edge;
            ways = 1;
        } else if (edge == minEdge) {
            ways++;
        }
    }
}

int main() {
    init();
    // for (int i = 1 ; i <= n+1 ; i++) {
    //     printf("i %d ps %d\n", i, psum[i]);
    //     psum[i] += psum[i-1];
    // }
    prepare();
    dfsSolve(0, 1, -1);
    dfsSolve(1, 1, -1);

    if (minEdge == 2) ways /= 2;

    printf("%d %d\n", minEdge, ways);
    return 0;
}