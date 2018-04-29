#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int match[N];
bool vis[N];
int n, m;
int row[N], col[N];
bool ada_row[N], ada_col[N];

int arr[N][N];
vector<int> adj[N];

bool pasti[N][N];

void read() {
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= m ; j++)
            cin >> arr[i][j];
}

int augment(int now) {
    if(vis[now]) return 0;
    vis[now] = 1;
    for(int nex : adj[now])
        if(match[nex] == -1 || augment(match[nex])) {
            match[nex] = now;
            return 1;
        }
    return 0;
}

void mcbm() {
    memset(match, -1, sizeof match);
    for(int i = 1 ; i <= n ; i++) {
        memset(vis, 0, sizeof vis);
        augment(i);
    }

    for(int i = 1 ; i <= m ; i++)
        if(match[i] != -1) {
            ada_row[match[i]] = ada_col[i] = 1;
        }
}

void make() {
    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= m ; j++) {
            row[i] = max(row[i], arr[i][j]);
            col[j] = max(col[j], arr[i][j]);
        }
    
    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= m ; j++)
            if(row[i] == col[j] && arr[i][j] != 0 && row[i] != 0) {
                adj[i].push_back(j);
            }
}

long long solve() {
    mcbm();
    
    long long ret = 0;
    int use = 0;
    vector<int> v;

    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= m ; j++) {
            if(arr[i][j] > 0)
                v.push_back(arr[i][j]);
        }
    
    for(int i = 1 ; i <= n ; i++) {
        if(row[i]) {
            ret -= row[i];
            use++;
        }
    }
    
    for(int j = 1 ; j <= m ; j++) {
        if(ada_col[j] || col[j] == 0) continue;
        ret -= col[j];
        use++;
    }
    
    for(int x : v) {
        ret += x;
    }
    
    ret -= ((int)v.size() - use);
    
    return ret;
}

int main() {
    read();
    make();
    cout << solve() << endl;
    return 0;
}
