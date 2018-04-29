#include "citymapping.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int n;
long long dist[N][N];
vector<int> chld[N];
int par[N];

long long get_dist(int a, int b) {
    if(dist[a][b] == -1) {
        dist[a][b] = dist[b][a] = get_distance(a, b); 
    }

    return dist[a][b];
}

void dfs_distance(int source, int now, int prv) {
    if(now != 1 && prv != par[now]) {
        int nxt = par[now];

        dist[source][nxt] = dist[source][now] + get_dist(now, nxt);
        dist[nxt][source] = dist[source][nxt];

        dfs_distance(source, nxt, now);
    }

    for(int nxt : chld[now]) {
        if(prv == nxt) {
            continue;
        }

        dist[source][nxt] = dist[source][now] + get_dist(now, nxt);
        dist[nxt][source] = dist[source][nxt];

        dfs_distance(source, nxt, now);
    }
}

int get_parent(int x) {
    int ans = 1;

    for(int child : chld[1]) {
        if(get_dist(1, child) + get_dist(child, x) == get_dist(1, x)) {
            ans = child;
            break;
        }
    }

    if(ans == 1) {
        return ans;
    }

    while(1) {
        int now = ans;
        
        if(chld[now].size() == 0) {
            return ans;
        } else if(chld[now].size() == 2) {
            int child = chld[now][0];

            if(get_dist(1, child) + get_dist(child, x) == get_dist(1, x)) {
                ans = child;
            } else {
                ans = chld[now][1];
            }
        } else {
            vector<int> v;

            while(chld[now].size() == 1) {
                v.push_back(chld[now][0]);
                now = chld[now][0];
            }

            // after chain
            v.push_back(now);

            int lo = 0, hi = v.size()-1;

            while(lo <= hi) {
                int mid = (lo + hi) / 2;
                int idx = v[mid];

                if(get_dist(1, idx) + get_dist(idx, x) == get_dist(1, x)) {
                    ans = idx;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }

            if(chld[ans].size() != 2) {
                return ans;
            }
        }
    }

    return -1;
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
        chld[parent].push_back(now);

        dfs_distance(now, now, -1);

        A[i] = now;
        B[i] = parent;
        W[i] = get_dist(now, parent);

        i++;
    }

	return;
}
