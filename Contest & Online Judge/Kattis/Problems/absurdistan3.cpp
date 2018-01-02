#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> adj[N];
int u[N], v[N];
bool vis[N];
bool used[N];
bool in_cycle[N];
int n;

vector<pair<int, int>> ans;

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d %d", &u[i], &v[i]);

        adj[u[i]].push_back(i);
        adj[v[i]].push_back(i);
    }
}

void dfs(int now) {
    vis[now] = 1;

    for(int num : adj[now]) {
        if(used[num]) continue;
        used[num] = 1;

        int nex = u[num] ^ v[num] ^ now;
        ans.push_back({now, nex});

        if(!vis[nex]) {
            dfs(nex);
            in_cycle[now] |= in_cycle[nex];
        } else {
            in_cycle[now] = 1;
        }
    }
}

void work() {
    for(int i = 1 ; i <= n ; i++) {
        if(!vis[i]) {
            dfs(i);
        }
    }
    
    for(pair<int, int> x : ans) {
        int u = x.first;
        int v = x.second;

        if(in_cycle[u] && in_cycle[v]) {
            printf("%d %d\n", u, v);
        } else {
            printf("%d %d\n", v, u);
        }
    }
}

int main() {
    read();
    work();
    return 0;
}