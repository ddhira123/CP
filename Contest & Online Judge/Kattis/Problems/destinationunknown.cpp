#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 5;
const int INF = 1e9 + 5;

vector<pair<int, int>> adj[N];
int dist[N];
int use[N];
int en[N];

int n, m, k;
int s, g, h;

void read() {
    scanf("%d %d %d", &n, &m, &k);
    scanf("%d %d %d", &s, &g, &h);

    for(int i = 0 ; i < m ; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    for(int i = 1 ; i <= k ; i++) {
        scanf("%d", &en[i]);
    }
}

void dijkstra() {
    for(int i = 1 ; i <= n ; i++) {
        dist[i] = INF;
        use[i] = 0;
    }

    priority_queue<pair<int, int>> pq;
    dist[s] = 0;
    pq.push({0, s});

    while(!pq.empty()) {
        pair<int, int> now = pq.top();
        pq.pop();

        if(dist[now.second] != -now.first) continue;

        for(auto it : adj[now.second]) {
            int nex = it.first;
            int ndis = dist[now.second] + it.second;
            int nuse = (g == now.second && h == nex) || (g == nex && h == now.second);
            nuse |= use[now.second];
            
            if(dist[nex] > ndis) {
                use[nex] = nuse;
                dist[nex] = ndis;

                pq.push({-ndis, nex});
            } else if(dist[nex] == ndis) {
                use[nex] |= nuse;
            }
        }
    }
}

void work() {
    dijkstra();
    vector<int> ans;

    for(int i = 1 ; i <= k ; i++) {
        if(use[en[i]]) {
            ans.push_back(en[i]);
        }
    }

    sort(ans.begin(), ans.end());
    for(int i = 0 ; i < ans.size() ; i++) {
        printf("%d%c", ans[i], i+1 == ans.size() ? '\n' : ' ');
    }
}

void reset() {
    for(int i = 1 ; i <= n ; i++) {
        adj[i].clear();
    }
}

int main() {
    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        work();
        reset();
    }
    return 0;
}