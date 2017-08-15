#include <bits/stdc++.h>
using namespace std;

const int N = 50005;
const int LOG = 17;

int depth[N];
int anc[N][LOG];

int cycle_size;
int cycle_order[N];
int root_num[N];

vector<int> adj[N];
int deg[N];

int n, q;

void reset() {
    memset(cycle_order, -1, sizeof cycle_order);
    memset(root_num, -1, sizeof root_num);
    memset(depth, -1, sizeof depth);

    for(int i = 0 ; i < N ; i++) {
        adj[i].clear();
        deg[i] = 0;
    }

    cycle_size = 0;
}

void build_st(int cur, int prv) {
    depth[cur] = depth[prv]+1;
    anc[cur][0] = prv;

    for(int i = 1 ; (1<<i) <= depth[cur] ; i++) {
        anc[cur][i] = anc[anc[cur][i-1]][i-1];
    }
}

int get_lca(int u, int v) {
    if(depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];

    for(int i = 0 ; diff ; i++)
        if(diff & (1 << i)) {
            diff -= (1 << i);
            u = anc[u][i];
        }

    if(u == v)
        return u;

    for(int i = LOG-1 ; i >= 0 ; i--)
        if(depth[u] >= (1 << i) && anc[u][i] != anc[v][i]) {
            u = anc[u][i];
            v = anc[v][i];
        }

    return anc[u][0];
}

void dfs_tree(int root, int now) {
    root_num[now] = root;

    for(int nex : adj[now]) {
        if(depth[nex] == -1 && cycle_order[nex] == -1) {
            depth[nex] = depth[now]+1;

            build_st(nex, now);
            dfs_tree(root, nex);
        }
    }
}

void init() {
    for(int i = 1 ; i <= n ; i++)
        for(int nex : adj[i]) {
            deg[nex]++;
        }

    queue<int> q;
    for(int i = 1 ; i <= n ; i++)
        if(deg[i] == 1) {
            q.push(i);
        }

    while(!q.empty()) {
        int now = q.front();
        q.pop();

        for(int nex : adj[now]) {
            deg[nex]--;

            if(deg[nex] == 1) {
                q.push(nex);
            }
        }
    }

    int st = -1;
    for(int i = 1 ; i <= n ; i++)
        if(deg[i] == 2) {
            st = i;
            break;
        }

    while(1) {
        cycle_order[st] = cycle_size++;
        depth[st] = 0;

        int nxt = -1;
        for(int nex : adj[st]) {
            if(deg[nex] == 2 && cycle_order[nex] == -1) {
                nxt = nex;
                break;
            }
        }

        if(nxt == -1) {
            break;
        } else {
            st = nxt;
        }
    }

    for(int i = 1 ; i <= n ; i++)
        if(cycle_order[i] != -1)
            dfs_tree(i, i);
}

pair<int, int> get_answer(int u, int v) {
    // both is in the cycle
    if(cycle_order[u] != -1 && cycle_order[v] != -1) {
        int diff = abs(cycle_order[u] - cycle_order[v]);
        int other_way = cycle_size - diff;

        return {2, diff * other_way};
    } else 
    // u is not in cycle; answer is from u to cycle
    if(cycle_order[u] == -1 && cycle_order[v] != -1) {
        return {1, depth[u]};
    } else 
    // v is not in cycle; answer is from v to cycle
    if(cycle_order[u] != -1 && cycle_order[v] == -1) {
        return {1, depth[v]};
    } else 
    // both not in cycle, and from different tree; answer is sum of depth
    if(root_num[u] != root_num[v]) {
        return {1, depth[u] + depth[v]};
    } else {
        // both not in cycle, same tree; answer is distance between them
        return {1, depth[u] + depth[v] - 2 * depth[get_lca(u, v)]};
    }
}

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void work() {
    scanf("%d", &q);

    for(int i = 1 ; i <= q ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        pair<int,int> answer = get_answer(u, v);
        printf("%d %d\n", answer.first, answer.second);
    }
}

int main() {
    int t; scanf("%d", &t);

    for(int tc = 1 ; tc <= t ; tc++) {
        reset();
        read();
        init();
        work();
    }
    return 0;
}
