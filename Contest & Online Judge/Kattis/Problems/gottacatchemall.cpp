#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

vector<int> adj[N];
set<pair<int, int>> seen;
unordered_set<int> neigh[N];
int n;

void read() {
    scanf("%d", &n);

    for (int i = 1 ; i < n ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        if (v > u) swap(u, v);
        if (seen.count({u, v})) continue;

        seen.insert({u, v});
        adj[u].push_back(v);
        adj[v].push_back(u);

        neigh[u].insert(v);
        neigh[v].insert(u);
    }
}

void prepare() {
    for (int i = 1 ; i <= n ; i++) {
        sort(adj[i].begin(), adj[i].end());
    }
}

long long calcTwo() {
    long long ret = 0;
    for (int i = 1 ; i <= n ; i++) {
        long long x = adj[i].size();
        // printf("i %d x %lld\n", i, x);
        ret += x * (x-1);
    }
    return ret;
}

int calcTriangle() {
    int ret = 0;
    // for (int i = 1 ; i <= n ; i++) {
    //     for (int j : adj[i]) {
    //         int k = adj[i].size() < adj[j].size() ? i : j;
    //         int l = i ^ j ^ k;

    //         for (int x : adj[k]) {
    //             if (x == j || x == i) continue;
    //             ret += neigh[l].count(x);
    //         }
    //     }
    // }
    for (int i = 1 ; i <= n ; i++) {
        for (int j : adj[i]) {
            if (j < i) continue;

            int a = adj[i].size() - (upper_bound(adj[i].begin(), adj[i].end(), j) - adj[i].begin());
            int b = adj[j].size() - (upper_bound(adj[j].begin(), adj[j].end(), j) - adj[j].begin());

            int k = a < b ? i : j;
            int l = i ^ j ^ k;

            int start = upper_bound(adj[k].begin(), adj[k].end(), j) - adj[k].begin();

            for (int it = start ; it < adj[k].size() ; it++) {
                int x = adj[k][it];
                if (x == j || x == i) continue;
                ret += neigh[l].count(x);
            }
        }
    }
    return 6 * ret;
}

int main() {
    read();
    prepare();

    long long a = calcTwo();
    long long b = calcTriangle();

    // printf("%lld %lld\n", a, b);
    printf("%lld\n", a-b);
    return 0;
}