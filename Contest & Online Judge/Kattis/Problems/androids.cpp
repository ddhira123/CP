#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int pset[N];
vector<pair<int, int>> v[3];
vector<pair<int, pair<int, int>>> elist;

int n;

int finds(int x) {
    return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

void join(int u, int v) {
    u = finds(u);
    v = finds(v);

    if(u != v) {
        pset[u] += pset[v];
        pset[v] = u;
    }
}

void read() {
    scanf("%d", &n);

    for(int i = 1 ; i <= n ; i++) {
        for(int j = 0 ; j < 3 ; j++) {
            int x; scanf("%d", &x);

            v[j].push_back({x, i});
        }
    }
}

void prepare() {
    memset(pset, -1, sizeof pset);

    for(int it = 0 ; it < 3 ; it++) {
        sort(v[it].begin(), v[it].end());

        for(int i = 1 ; i < v[it].size() ; i++) {
            int a = v[it][i-1].second;
            int b = v[it][i].second;

            int w = v[it][i].first - v[it][i-1].first;

            elist.push_back({w, {a, b}});
        }
    }
}

int work() {
    sort(elist.begin(), elist.end());
    int ret = 0;

    for(auto it : elist) {
        int w = it.first;
        int a = it.second.first;
        int b = it.second.second;

        if(finds(a) != finds(b)) {
            ret += w;
            join(a, b);
        }
    }

    return ret;
}

int main() {
    read();
    prepare();
    printf("%d\n", work());
    return 0;
}