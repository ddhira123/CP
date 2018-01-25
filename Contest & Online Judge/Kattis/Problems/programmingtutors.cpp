#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int x[2][N], y[2][N];
int n;

vector<int> adj[N];
bool vis[N];
int match[N];

void read() {
    cin >> n;
    for(int i = 0 ; i < 2 ; i++) {
        for(int j = 1 ; j <= n ; j++) {
            cin >> x[i][j] >> y[i][j];
        }
    }
}

void build_graph(int lim) {
    for(int i = 1 ; i <= n ; i++) {
        adj[i].clear();
        for(int j = 1 ; j <= n ; j++) {
            if(abs(x[0][i] - x[1][j]) + abs(y[0][i] - y[1][j]) <= lim) {
                adj[i].push_back(j);
            }
        }
    }
}

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

int mcbm(int lim) {
    build_graph(lim);
    memset(match, -1, sizeof match);

    int ret = 0;
    for(int i = 1 ; i <= n ; i++) {
        memset(vis, 0, sizeof vis);
        ret += augment(i);
    }

    return ret;
}

int work() {
    int lo = 0, hi = 1e9;

    while(lo < hi) {
        int mid = (lo + hi) / 2;

        if(mcbm(mid) == n) {
            hi = mid;
        } else {
            lo = mid+1;
        }
    }

    return lo;
}

int main() {
    read();
    cout << work() << endl;
    return 0;
}