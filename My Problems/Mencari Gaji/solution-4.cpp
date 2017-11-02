#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, m, k, s;
vector<int> adj[N];
bool differentWithS[N];
int p;

int val[N];
int vis[N];

void read() {
    scanf("%d %d %d %d", &n, &m, &k, &s);
    for(int i = 0 ; i < m ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[v].push_back(u);
    }
    for(int i = 0 ; i < k ; i++) {
        int x; scanf("%d", &x);
        differentWithS[x] = true;
    }
    scanf("%d", &p);
}

bool dfs(int now) {
    if(vis[now] == 2) {
        return true;
    }
    if(vis[now] == 1) {
        return false;
    }

    vis[now] = 2;

    bool ret = false;
    for(int nex : adj[now]) {
        ret |= dfs(nex);
    }

    vis[now] = 1;

    return ret;
}

bool hasCycle() {
    memset(vis, -1, sizeof vis);
    
    for(int i = 1 ; i <= n ; i++)
        if(vis[i] == -1 && dfs(i)) {
            return true;
        }

    return false;
}

int get(int now) {
    int &ret = val[now];
    if(ret != -1) {
        return ret;
    }

    ret = 0;
    for(int nex : adj[now]) {
        ret = max(ret, get(nex));
    }
    ret++;

    return ret;
}

void solve() {
    vector<int> different;
    for(int i = 1 ; i <= n ; i++)
        if(differentWithS[i]) {
            different.push_back(i);
        }

    vector<int> ans;

    for(int i = 0 ; i < (1 << different.size()) ; i++) {
        for(int j = 0 ; j < different.size() ; j++)
            if(i & (1 << j)) {
                adj[different[j]].push_back(s);
            } else {
                adj[s].push_back(different[j]);
            }

        if(!hasCycle()) {
            memset(val, -1, sizeof val);

            vector<int> temp(n);
            for(int i = 1 ; i <= n ; i++) {
                temp[i-1] = get(i);
            }

            if(ans.empty() || temp < ans) {
                ans = temp;
            }
        }

        for(int j = 0 ; j < different.size() ; j++)
            if(i & (1 << j)) {
                adj[different[j]].pop_back();
            } else {
                adj[s].pop_back();
            }
    }

    for(int i = 0 ; i < ans.size() ; i++)
        printf("%d%c", ans[i], i+1 == n ? '\n' : ' ');
}

int main() {
    read();
    solve();
    return 0;
}
