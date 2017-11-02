#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, m, k, s;
vector<int> adj[N];
bool differentWithS[N];
int p;

vector<int> rAdj[N];
int deg[N];

void read() {
    scanf("%d %d %d %d", &n, &m, &k, &s);
    for(int i = 0 ; i < m ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[v].push_back(u);
        rAdj[u].push_back(v);
    }
    for(int i = 0 ; i < k ; i++) {
        int x; scanf("%d", &x);
        differentWithS[x] = true;
    }
    scanf("%d", &p);
}

void solve() {
    for(int i = 1 ; i <= n ; i++)
        for(int nex : adj[i])
            rAdj[nex].push_back(i);

    for(int i = 1 ; i <= n ; i++)
        for(int nex : rAdj[i])
            deg[nex]++;

    queue<int> q;
    for(int i = 1 ; i <= n ; i++)
        if(deg[i] == 0) {
            q.push(i);
        }

    vector<int> ans(n);
    for(int i = 1 ; i <= n ; i++) {
        int now = q.front();
        q.pop();

        ans[now-1] = i;
        for(int nex : rAdj[now]) {
            deg[nex]--;
            if(deg[nex] == 0) {
                q.push(nex);
            }
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