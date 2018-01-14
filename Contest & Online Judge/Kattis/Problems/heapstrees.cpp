#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int p[N], v[N];
int n;
multiset<int> st[N];
int use[N];

void read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d %d", &v[i], &p[i]);
    }
}

int solve() {
    for(int i = 1 ; i <= n ; i++) {
        use[i] = i;
    }

    for(int i = n ; i >= 1 ; i--) {
        auto it = st[use[i]].upper_bound(v[i] - 1);
        if(it != st[use[i]].end()) {
            st[use[i]].erase(it);
        }
        st[use[i]].insert(v[i]);

        int par = p[i];
        int upar = use[par];

        if(st[use[i]].size() < st[upar].size()) {
            st[upar].insert(st[use[i]].begin(), st[use[i]].end());
        } else {
            st[use[i]].insert(st[upar].begin(), st[upar].end());
            use[par] = use[i];
        }
    }

    return st[use[0]].size();
}

int main() {
    read();
    printf("%d\n", solve());
    return 0;
}