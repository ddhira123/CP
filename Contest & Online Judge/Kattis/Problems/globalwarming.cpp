#include <bits/stdc++.h>
using namespace std;

const int N = 255;
const int MAX_SIZE = 22;
const int IMPOSSIBLE = -1;
const int INF = 1e9;

int dp[1 << MAX_SIZE];

int arr[N][N];
bool vis[N];
int val[MAX_SIZE][MAX_SIZE];

int n, m;

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0 ; i < m ; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        arr[u][v] = arr[v][u] = w;
    }
}

void fetch(int now, vector<int> &v) {
    vis[now] = true;
    v.push_back(now);

    for(int i = 1 ; i <= n ; i++) {
        if(!vis[i] && arr[now][i] != -1) {
            fetch(i, v);
        }
    }
}

int solve_component(int now) {
    vector<int> seen;
    fetch(now, seen);

    // cout << now << " " << seen.size() << endl;

    if(seen.size() & 1) {
        return IMPOSSIBLE;
    }

    for(int i = 0 ; i < seen.size() ; i++)
        for(int j = 0 ; j < seen.size() ; j++) {
            if(i != j) {
                int a = seen[i];
                int b = seen[j];

                assert(arr[a][b] != -1);

                val[i][j] = arr[a][b];
            }
        }

    dp[0] = 0;
    for(int i = 1 ; i < (1 << seen.size()) ; i++) {
        if(__builtin_popcount(i) & 1) continue;

        dp[i] = INF;
        for(int j = 0 ; j < seen.size() ; j++)
            if(i & (1 << j)) {
                for(int k = j+1 ; k < seen.size() ; k++) {
                    if(i & (1 << k)) {
                        int nmask = i ^ (1 << j) ^ (1 << k);

                        dp[i] = min(dp[i], dp[nmask] + val[j][k]);
                    }
                }

                break;
            }
    }

    return dp[(1 << seen.size()) - 1];
}

int solve() {
    int ret = 0;
    for(int i = 1 ; i <= n ; i++) {
        if(!vis[i]) {
            int temp = solve_component(i);

            if(temp == IMPOSSIBLE) return IMPOSSIBLE;

            ret += temp;
        }
    }
    return ret;
}

int main() {
    memset(arr, -1, sizeof arr);

    read();
    int ret = solve();

    if(ret == IMPOSSIBLE) puts("impossible");
    else printf("%d\n", ret);
    return 0;
}