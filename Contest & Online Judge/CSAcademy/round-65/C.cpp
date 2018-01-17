#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> adj[N];
int nxt[N];
int n;

int dfs(int now, int prv, int depth) {
    int best = depth;

    nxt[now] = -1;
    for(int nex : adj[now]) {
        if(nex == prv) continue;
        int from_nex = dfs(nex, now, depth+1);

        if(from_nex > best) {
            best = from_nex;
            nxt[now] = nex;
        }
    }

    return best;
}

int init_path() {
    dfs(1, -1, 0);
    int now = 1;

    while(nxt[now] != -1) {
        now = nxt[now];
    }

    dfs(now, -1, 0);

    // for(int i = 1 ; i <= n ; i++) {
    //     // cout << i << " " << nxt[i] << endl;
    // }

    return now;
}

void get_path(int now, int par, int is_longest, vector<int> &v) {
    // cout << now << " " << nxt[now] << endl;

    v.push_back(now);
    for(int nex : adj[now]) {
        if(nex == par) continue;

        if(!is_longest || nex != nxt[now]) {
            get_path(nex, now, 0, v);
        }
    }

    if(!is_longest) {
        v.push_back(par);
    } else if(nxt[now] != -1) {
        get_path(nxt[now], now, 1, v);
    }
}

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i < n ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void work() {
    int start = init_path();
    vector<int> ret;

    get_path(start, -1, 1, ret);

    cout << ret.size()-1 << endl;
    bool space = false;

    for(int x : ret) {
        if(space) printf(" ");
        else space = true;

        printf("%d", x);
    }

    puts("");
}

int main() {
    read();
    work();
    return 0;
}