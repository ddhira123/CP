#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const long long INF = 4e18;
const int MOD = 1e9 + 7;

int n, m, s, t;
vector<pair<int, int>> adj[N];

long long dist[2][N];
int dp[2][N];

long long tmp[N];

void read() {
    scanf("%d %d", &n, &m);
    scanf("%d %d", &s, &t);

    for(int i = 0 ; i < m ; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
}

void dijkstra(int source, int id) {
    for(int i = 1 ; i <= n ; i++) {
        dist[id][i] = INF;
    }

    dist[id][source] = 0;
    dp[id][source] = 1;
    priority_queue<pair<long long, int>> pq;

    pq.push({0, source});

    while(!pq.empty()) {
        int cur = pq.top().second;
        long long dis = -pq.top().first;
        pq.pop();
        // cout << id << " " << cur << " " << dis << " " << dist[id][cur] << endl;

        if(dis != dist[id][cur]) continue;

        for(auto it : adj[cur]) {
            int nxt = it.first;
            long long ndis = dis + it.second;

            if(ndis == dist[id][nxt]) {
                dp[id][nxt] = (dp[id][nxt] + dp[id][cur]) % MOD;
            } else if(ndis < dist[id][nxt]) {
                dp[id][nxt] = dp[id][cur];
                dist[id][nxt] = ndis;

                pq.push({-ndis, nxt});
            }
        }
    }

    // for(int i = 1 ; i <= n ; i++) {
    //     printf("[%d][%d] -> %lld %d\n", id, i, dist[id][i], dp[id][i]);
    // }
}

void prepare() {
    dijkstra(t, 0);
    dijkstra(s, 1);
}

int work() {
    int ret = dp[0][s];
    ret = 1ll * ret * ret % MOD;
    
    int kurang = 0;

    for(int i = 1 ; i <= n ; i++) {
        if(dist[0][i] + dist[1][i] == dist[0][s] && dist[0][i] == dist[1][i]) {
            int ways = 1ll * dp[0][i] * dp[1][i] % MOD;
            ways = 1ll * ways * ways % MOD;
            kurang = (kurang + ways) % MOD;
        }
    }

    int kurang_e = 0;

    for(int i = 1 ; i <= n ; i++) {
        for(auto it : adj[i]) {
            if(dist[0][i] * 2 < dist[0][s] && dist[1][it.first] * 2 < dist[0][s] && 
                dist[0][i] + dist[1][it.first] + it.second == dist[0][s]) {
                int ways = 1ll * dp[0][i] * dp[1][it.first] % MOD;
                ways = 1ll * ways * ways % MOD;
                kurang_e = (kurang_e + ways) % MOD;
            }
        }
    }

    kurang = (kurang + kurang_e) % MOD;
    ret = (ret - kurang + MOD) % MOD;
    return ret;

    // memset(dp, 0, sizeof dp);

    // vector<int> v[2];
    // v[0] = {s};
    // v[1] = {t};

    // dp[0][s] = 1;
    // dp[1][t] = 1;

    // int kurang = 0;
    // // cout << ret << endl;
    // do {
    //     static int cntr = 0;
    //     cntr++;
    //     // cout << cntr << endl;
    //     for(int i = 0 ; i < 2 ; i++) {
    //         for(int x : v[i]) {
    //             tmp[x] = dp[i][x];
    //             dp[i][x] = 0;
    //         }

    //         set<int> seen;
    //         for(int x : v[i]) {
    //             for(pair<int, int> nex : adj[x]) {
    //                 if(dist[i][x] - nex.second == dist[i][nex.first]) {
    //                     kurang = (kurang + 1ll * tmp[x] * dp[i^1][nex.first]) % MOD;
    //                     dp[i][nex.first] = (dp[i][nex.first] + tmp[x]) % MOD;

    //                     seen.insert(nex.first);
    //                 }
    //             }
    //         }

    //         v[i].clear();
    //         for(auto it : seen) {
    //             v[i].push_back(it);
    //         }
    //     }
    // } while(!v[0].empty() && !v[1].empty());

    // ret = (ret - kurang + MOD) % MOD;
    // return ret;
}

int main() {
    read();
    prepare();
    cout << work() << endl;
    return 0;
}