#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const int MOD = 1e9 + 7;

vector<pair<int, int>> adj[N];
bool vis[N];
int n, m;

void dfs(int now) {
    if(vis[now]) return;
    vis[now] = true;

    for(pair<int,int> edge: adj[now]) {
        dfs(edge.first);
    }
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

int get_answer() {
    dfs(1);

    return vis[n] ? 0 : -1;
}

int main() {
    read();
    printf("%d\n", get_answer());
    return 0;
}
