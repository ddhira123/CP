#include "citymapping.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n;
long long dist[N][N];
vector<int> chld[N];
vector<int> adj[N];

int par[N];
int heavy[N];
int sz[N];
int max_sz[N];
int depth[N];
int blocked[N];


vector<int> seen;

long long get_dist(int a, int b) {
    if(dist[a][b] == -1) {
        dist[a][b] = dist[b][a] = get_distance(a, b); 
    }

    return dist[a][b];
}

void dfs_distance(int source, int now, int prv) {
    if(now != 1 && prv != par[now]) {
        int nxt = par[now];

        dist[source][nxt] = get_dist(source, now) + get_dist(now, nxt);
        dist[nxt][source] = dist[source][nxt];

        dfs_distance(source, nxt, now);
    }

    for(int nxt : chld[now]) {
        if(prv == nxt) {
            continue;
        }

        dist[source][nxt] = get_dist(source, now) + get_dist(now, nxt);
        dist[nxt][source] = dist[source][nxt];

        dfs_distance(source, nxt, now);
    }
}

// void dfs_heavy(int now) {
//     heavy[now] = -1;
//     sz[now] = 1;

//     for(int nxt : chld[now]) {
//         dfs_heavy(nxt);

//         sz[now] += sz[nxt];
//         if(heavy[now] == -1 || sz[nxt] > sz[heavy[now]]) {
//             heavy[now] = nxt;
//         }
//     }
// }

void dfs_centroid(int now, int prv) {
    seen.push_back(now);

    sz[now] = 1;
    max_sz[now] = 0;

    for(int nex : adj[now]) {
        if(prv != nex && !blocked[nex]) {
            dfs_centroid(nex, now);

            sz[now] += sz[nex];
            max_sz[now] = max(max_sz[now], sz[nex]);
        }
    }
}

int get_parent(int x) {
    memset(blocked, 0, sizeof blocked);
    int ans = 1;

    while(1) {
        int root = ans;
        seen.clear();

        dfs_centroid(root, -1);

        if(seen.size() <= 4) {
            sort(seen.begin(), seen.end(), [&](int a, int b) {
                return depth[a] > depth[b];
            });

            for(int it : seen) {
                if(get_dist(1, it) + get_dist(it, x) == get_dist(1, x)) {
                    return it;
                }
            }
        }

        for(int it : seen) {
            max_sz[it] = max(max_sz[it], sz[ans] - sz[it]);

            if(max_sz[it] < max_sz[root]) {
                root = it;
            }
        }

        int nxt = root;
        for(int it : chld[root]) {
            if(!blocked[it]) {
                if(get_dist(1, it) + get_dist(it, x) == get_dist(1, x)) {
                    nxt = it;
                    break;
                }
            }
        }

        if(nxt != root) {
            blocked[root] = true;
            // printf("block %d\n", root);
            ans = nxt;
        } else {
            ans = root;
            for(int it : chld[root]) {
                blocked[it] = true;
                // printf("block %d\n", it);
            }
        }
    }
}

void find_roads(int N, int Q, int A[], int B[], int W[]) {
	memset(dist, -1, sizeof dist);
    for(int i = 1 ; i <= N ; i++) {
        dist[i][i] = 0;
    }
    n = N;

    vector<pair<long long, int>> v;
    for(int i = 2 ; i <= n ; i++) {
        v.push_back({get_dist(1, i), i});
    }

    sort(v.begin(), v.end());
    int i = 0;

    for(auto it : v) {
        int now = it.second;

        int parent = get_parent(now);

        par[now] = parent;
        depth[now] = depth[parent] + 1;
        chld[parent].push_back(now);

        adj[parent].push_back(now);
        adj[now].push_back(parent);

        // dfs_distance(now, now, -1);
        // dfs_heavy(1);

        A[i] = now;
        B[i] = parent;
        W[i] = get_dist(now, parent);

        // printf("%d %d %d\n", A[i], B[i], W[i]);

        i++;
    }

	return;
}
