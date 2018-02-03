#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<pair<int, int>> adj[N];
int n, m;
int dist[N];
bool vis[N];

bool dfs(int now) {
    vis[now] = true;

    bool ok = true;
    for(pair<int, int> nxt : adj[now]) {
        if(vis[nxt.first]) {
            if(dist[now] + nxt.second != dist[nxt.first]) {
                return false;
            }
        } else {
            dist[nxt.first] = dist[now] + nxt.second;
            ok &= dfs(nxt.first);
        }
    }

    return ok;
}

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0 ; i < m ; i++) {
        int l, r, d;
        scanf("%d %d %d", &l, &r, &d);

        adj[l].push_back({r, d});
        adj[r].push_back({l, -d});
    }
}

bool work() {
    for(int i = 1 ; i <= n ; i++) {
        if(!vis[i]) {
            if(!dfs(i)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    read();
    printf("%s\n", work() ? "Yes" : "No");
    return 0;
}