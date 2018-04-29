#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> adj[N];

int state[N];
int num[N], low[N];
int depth[N];
int fpb[N];

int n, m;
int u[N], v[N];

int scc;
bool ok;

int gcd(int a, int b) {
    return a == 0 ? b : gcd(b % a, a);
}

void tarjan(int now) {
    static int cnt = 0;

    num[now] = low[now] = ++cnt;
    state[now] = 1;

    for(int nex : adj[now]) {
        if(state[nex] == -1) {
            depth[nex] = depth[now] + 1;
            tarjan(nex);
        }
        if(state[nex] == 1)  {
            low[now] = min(low[now], low[nex]);
            if(depth[nex] <= depth[now]) {
                // printf("now %d fpb %d x %d\n", now, fpb[now], depth[now] - depth[nex] + 1);
                fpb[now] = gcd(fpb[now], depth[now] - depth[nex] + 1);
                fpb[now] = gcd(fpb[now], 1 + fpb[nex] + depth[now] - depth[nex]);
            } else {
                // printf("now %d fpb %d x %d\n", now, fpb[now], 1 + fpb[nex] - depth[nex] + depth[now]);
                fpb[now] = gcd(fpb[now], 1 + fpb[nex] - depth[nex] + depth[now]);
            }
        }
    }

    if(low[now] == num[now]) {
        ok &= (fpb[now] == 1);
        scc++;
    }
}

bool read() {
    scanf("%d %d", &n, &m);
    for(int i = 0 ; i < m ; i++) {
        scanf("%d %d", &u[i], &v[i]);
    }

    return n > 0 || m > 0;
}

void prepare() {
    for(int i = 1 ; i <= n ; i++) {
        adj[i].clear();
        state[i] = -1;
        depth[i] = 0;
        fpb[i] = 0;
    }
    scc = 0;
    ok = true;

    set<pair<int, int>> st;

    for(int i = 0 ; i < m ; i++) {
        if(!st.count({u[i], v[i]})) {
            adj[u[i]].push_back(v[i]);
            st.insert({u[i], v[i]});
        }
    }
}

bool work() {
    for(int i = 1 ; i <= n ; i++) {
        if(state[i] == -1) {
            tarjan(i);
        }
    }

    ok &= (scc == 1);

    return ok;
}

int main() {
    while(read()) {
        prepare();
        printf("%c\n", work() ? 'Y' : 'N');
    }
    return 0;
}
