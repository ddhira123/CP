#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;

vector<pair<int, pair<int, int>>> elist;
int pset[N];
vector<int> sources;

int n, m, l, s;

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
    scanf("%d %d %d %d", &n, &m, &l, &s);

    sources.resize(s);
    for(int &it : sources) {
        scanf("%d", &it);
    }

    elist.resize(m);
    for(auto &it : elist) {
        scanf("%d %d %d", &it.second.first, &it.second.second, &it.first);
    }
}

long long solve() {
    long long ret = 1ll * l * (n - sources.size());

    for(int it : sources) {
        join(sources[0], it);
    }

    sort(elist.begin(), elist.end());
    for(auto it : elist) {
        int cost = it.first;
        int x = it.second.first;
        int y = it.second.second;

        x = finds(x);
        y = finds(y);

        if(x != y) {
            ret += cost;
            join(x, y);
        }
    }

    return ret;
}

void reset() {
    memset(pset, -1, sizeof pset);
    elist.clear();
    sources.clear();
}

int main() {
    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        reset();
        read();
        printf("%lld\n", solve());
    }
    return 0;
}