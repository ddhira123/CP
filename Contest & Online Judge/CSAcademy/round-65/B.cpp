#include <bits/stdc++.h>
using namespace std;

int n;
set<pair<int, int>> s;

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i < n ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        if(u > v) swap(u, v);
        s.insert({u, v});
    }

    int ret = 0;
    for(int i = 1 ; i < n ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        if(u > v) swap(u, v);
        ret += s.count({u, v});
    }

    cout << ret << endl;
    return 0;
}