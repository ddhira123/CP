#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int pset[N];
int red[N];
int blue[N];
int n;

void init() {
    memset(pset, -1, sizeof pset);
}

int finds(int x) {
    return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

int join(int u, int v, int w) {
    u = finds(u);
    v = finds(v);

    if(u != v) {
        pset[u] = v;
        return w;
    }

    return 0;
}

void read() {
    cin >> n;
    for(int i = 1 ; i <= n ; i++) cin >> red[i];
    for(int i = 1 ; i <= n ; i++) cin >> blue[i];
}

long long work() {
    init();

    vector<pair<long long, pair<int, int>>> v;
    for(int i = 1 ; i <= n ; i++)
        for(int j = i+1 ; j <= n ; j++) {
            v.push_back({red[i] ^ blue[j], {i, j}});
            v.push_back({red[j] ^ blue[i], {i, j}});
        }
    sort(v.begin(), v.end());

    long long ret = 0;
    for(auto it : v) {
        ret += join(it.second.first, it.second.second, it.first);
    }

    return ret;
}

int main() {
    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        printf("Case #%d: %lld\n", tc, work());
    }
    return 0;
}