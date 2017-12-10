#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

vector<vector<int>> v;
int n, m;
int pset[N];
vector<int> adj[N];
int dp[N];

int get(int x, int y) {
    return x * m + y;
}

int finds(int x) {
    return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

void join(int x, int y) {
    x = finds(x);
    y = finds(y);
    if(x != y) {
        pset[x] += pset[y];
        pset[y] = x;
    }
}

void read() {
    scanf("%d %d", &n, &m);
    v.resize(n, vector<int>(m, 0));

    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < m ; j++) {
            scanf("%d", &v[i][j]);
        }
}

void make_set() {
    for(int i = 0 ; i < n ; i++) {
        vector<pair<int, int>> arr;
        for(int j = 0 ; j < m ; j++) {
            arr.push_back({v[i][j], j});
        }

        sort(arr.begin(), arr.end());
        for(int j = 1 ; j < m ; j++) {
            if(arr[j].first == arr[j-1].first) {
                join(get(i, arr[j].second), get(i, arr[j-1].second));
            }
        }
    }

    for(int j = 0 ; j < m ; j++) {
        vector<pair<int, int>> arr;
        for(int i = 0 ; i < n ; i++) {
            arr.push_back({v[i][j], i});
        }

        sort(arr.begin(), arr.end());
        for(int i = 1 ; i < n ; i++) {
            if(arr[i].first == arr[i-1].first) {
                join(get(arr[i].second, j), get(arr[i-1].second, j));
            }
        }
    }
}

void make_graph() {
    for(int i = 0 ; i < n ; i++) {
        vector<pair<int, int>> arr;
        for(int j = 0 ; j < m ; j++) {
            arr.push_back({v[i][j], j});
        }

        sort(arr.begin(), arr.end());
        for(int j = 1 ; j < m ; j++) {
            if(arr[j].first != arr[j-1].first) {
                int u = finds(get(i, arr[j].second));
                int v = finds(get(i, arr[j-1].second));
                adj[u].push_back(v);
            }
        }
    }

    for(int j = 0 ; j < m ; j++) {
        vector<pair<int, int>> arr;
        for(int i = 0 ; i < n ; i++) {
            arr.push_back({v[i][j], i});
        }

        sort(arr.begin(), arr.end());
        for(int i = 1 ; i < n ; i++) {
            if(arr[i].first != arr[i-1].first) {
                int u = finds(get(arr[i].second, j));
                int v = finds(get(arr[i-1].second, j));
                adj[u].push_back(v);
            }
        }
    }
}

void init() {
    memset(pset, -1, sizeof pset);

    make_set();
    make_graph();
}

int solve(int x) {
    if(dp[x] != -1) return dp[x];

    dp[x] = 1;
    for(int nex : adj[x]) {
        dp[x] = max(dp[x], 1 + solve(nex));
    }

    return dp[x];
}

int work() {
    memset(dp, -1, sizeof dp);
    int ret = 0;

    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < m ; j++) {
            ret = max(ret, solve(finds(get(i, j))));
        }

    return ret;
}

int main() {
    read();
    init();
    cout << work() << endl;
    return 0;
}