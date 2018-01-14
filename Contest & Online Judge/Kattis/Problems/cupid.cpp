#include <bits/stdc++.h>
using namespace std;

const int N = 50005;
const int K = 1e6 + 5;
const int MAGIC = 300;

struct Query {
    int l;
    int r;
    int num;
};

int man[K], woman[K];
int a[N], b[N];
int n, m, k;

int ans[N];
Query query[N];

void add(int &ret, int x) {
    ret -= min(man[a[x]], woman[a[x]]);
    man[a[x]]++;
    ret += min(man[a[x]], woman[a[x]]);

    ret -= min(man[b[x]], woman[b[x]]);
    woman[b[x]]++;
    ret += min(man[b[x]], woman[b[x]]);
}

void remove(int &ret, int x) {
    ret -= min(man[a[x]], woman[a[x]]);
    man[a[x]]--;
    ret += min(man[a[x]], woman[a[x]]);

    ret -= min(man[b[x]], woman[b[x]]);
    woman[b[x]]--;
    ret += min(man[b[x]], woman[b[x]]);
}

void read() {
    scanf("%d %d %d", &n, &m, &k);

    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &a[i]);
    }

    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &b[i]);
    }


    for(int i = 0 ; i < m ; i++) {
        scanf("%d %d", &query[i].l, &query[i].r);
        query[i].num = i;
    }
}

void solve() {
    sort(query, query + m, [&](Query a, Query b) {
        if(a.l / MAGIC == b.l / MAGIC) {
            return a.r < b.r;
        }

        return a.l / MAGIC < b.l / MAGIC;
    });

    int l = 0, r = 0;
    int ret = 0;

    for(int i = 0 ; i < m ; i++) {
        while(r <= query[i].r) {
            add(ret, r);
            r++;
        }
        while(l-1 >= query[i].l) {
            l--;
            add(ret, l);
        }

        while(l < query[i].l) {
            remove(ret, l);
            l++;
        }
        while(r-1 > query[i].r) {
            r--;
            remove(ret, r);
        }

        ans[query[i].num] = ret;
    }

    for(int i = 0 ; i < m ; i++) {
        printf("%d\n", ans[i]);
    }
}

int main() {
    read();
    solve();
    return 0;
}