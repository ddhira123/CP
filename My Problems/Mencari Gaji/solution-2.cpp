#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, m, k, s;
vector<int> adj[N];
bool differentWithS[N];
int p;

vector<int> rAdj[N];
int deg[N];
bool done[N];

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

    vector<int> ans(n);
    
    for(int i = 1 ; i <= n ; i++) {
        int pos = -1;
        for(int j = 1 ; j <= n ; j++)
            if(!done[j] && deg[j] == 0) {
                pos = j;
            }

        done[pos] = true;
        ans[pos-1] = i;

        for(int nex : rAdj[pos]) {
            deg[nex]--;
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
