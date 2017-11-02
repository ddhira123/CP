#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, m, k, s;
vector<int> adj[N];
bool differentWithS[N];
int p;

int val[N];

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

    if(differentWithS[now] && ret == get(s)) {
        ret++;
    }

    return ret;
}

void solve() {
    vector<int> ans;

    memset(val, -1, sizeof val);

    for(int i = 1 ; i <= n ; i++) {
        ans.push_back(get(i));
    }

    for(int i = 0 ; i < ans.size() ; i++)
        printf("%d%c", ans[i], i+1 == n ? '\n' : ' ');
}

int main() {
    read();
    solve();
    return 0;
}
