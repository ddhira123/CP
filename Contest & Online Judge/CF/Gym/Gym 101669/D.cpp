#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int pset[N];
vector<int> v[N];

int finds(int x) {
    return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

void join(int x, int y) {
    x = finds(x);
    y = finds(y);

    if (x != y) {
        pset[x] += pset[y];
        pset[y] = x;
    }
}

int main() {
    memset(pset, -1, sizeof pset);

    int m, n;
    scanf("%d %d", &m, &n);

    for (int i = 0 ; i < m ; i++) {
        int k; scanf("%d", &k);

        for (int j = 0 ; j < k ; j++) {
            int x; scanf("%d", &x);
            v[x].push_back(i);
        }
    }

    int ans = 0;
    for (int i = 1 ; i <= n ; i++) {
        assert(v[i].size() == 2);

        int x = v[i][0];
        int y = v[i][1];

        // printf("x %d %d y %d %d\n", x, finds(x), y, finds(y));

        if (finds(x) != finds(y)) {
            ans++;
            join(x, y);
        }
    }

    printf("%d\n", ans);
    return 0;
}