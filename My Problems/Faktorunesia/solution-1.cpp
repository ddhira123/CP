#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const int MOD = 1e9 + 7;
const int MAX_STEP = 10;
const int INF = 1e9;

vector<pair<int, int>> adj[N];
int n, m;

void dfs(int now, int step, int fact, int total, int &ret) {
    if(now == n) {
        ret = min(ret, total);
    }

    if(step > MAX_STEP) {
        return;
    }

    for(pair<int,int> edge: adj[now]) {
        if(edge.second < step) {
            dfs(edge.first, step+1, fact * (step+1), total + fact * edge.second, ret);
        }
    }
}

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0 ; i < m ; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
}

int get_answer() {
    int ret = INF;
    dfs(1, 1, 1, 0, ret);

    return ret == INF ? -1 : ret;
}

int main() {
    read();
    printf("%d\n", get_answer());
    return 0;
}
