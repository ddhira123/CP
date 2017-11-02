#include <bits/stdc++.h>
using namespace std;

map<int, int> X, Y;
map<pair<int, int>, int> coord;

int main() {
    int n; scanf("%d", &n);

    for(int i = 0 ; i < n ; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        X[x]++;
        Y[y]++;
        coord[{x, y}]++;
    }

    int ret = 0;
    for(auto it : coord) {
        int x = it.first.first;
        int y = it.first.second;

        int cur = X[x] + Y[y] - 2 * it.second;
        // printf("%d %d -> %d %d %d\n", x, y, X[x], Y[y], it.second);
        ret = max(ret, cur);
    }

    printf("%d\n", ret);
    return 0;
}