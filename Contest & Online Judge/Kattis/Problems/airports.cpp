#include <bits/stdc++.h>
using namespace std;

const int N = 505;

int dist[N][N];
int ori_dist[N][N];
int inspect[N];
int s[N], f[N], t[N];
int n, m;

vector<int> adj[N];
int match[N];
bool vis[N];

int augment(int x) {
    if(vis[x]) return 0;
    vis[x] = 1;

    for(int nex : adj[x]) {
        if(match[nex] == -1 || augment(match[nex])) {
            match[nex] = x;
            return 1;
        }
    }

    return 0;
}

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &inspect[i]);
    }

    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= n ; j++) {
            scanf("%d", &dist[i][j]);
        }

    for(int i = 1 ; i <= m ; i++) {
        scanf("%d %d %d", &s[i], &f[i], &t[i]);
    }
}

void prepare() {
    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= n ; j++) {
            if(i != j) {
                dist[i][j] += inspect[j];
            }

            ori_dist[i][j] = dist[i][j];
        }

    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= n ; j++)
            for(int k = 1 ; k <= n ; k++) {
                dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
            }

    for(int i = 1 ; i <= m ; i++)
        for(int j = 1 ; j <= m ; j++) {
            int from_i = ori_dist[s[i]][f[i]] + t[i];
            from_i += dist[f[i]][s[j]];

            if(from_i <= t[j]) {
                adj[i].push_back(j);
            }
        }
}

int work() {
    memset(match, -1, sizeof match);
    int ret = m;

    for(int i = 1 ; i <= m ; i++) {
        memset(vis, 0, sizeof vis);
        ret -= augment(i);
    }

    return ret;
}

int main() {
    read();
    prepare();
    cout << work() << endl;
    return 0;
}