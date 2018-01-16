#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int C = 21;
const int MOD = 10007;

struct Node {
    int cnt[C];

    Node() {
        memset(cnt, 0, sizeof cnt);
    }

    void set(int idx, int val) {
        cnt[idx] = val;
    }

    Node operator +(Node other) const {
        Node ret;

        for(int i = 0 ; i < C ; i++)
            for(int j = 0 ; j < C ; j++) {
                int add = i + j;
                if(add >= C) add = C-1;

                ret.cnt[add] = (ret.cnt[add] + cnt[i] * other.cnt[j]) % MOD;
            }

        return ret;
    }

    int get_at_least(int c) {
        int ret = 0;
        for(int i = c ; i < C ; i++) {
            ret = (ret + cnt[i]) % MOD;
        }
        return ret;
    }
};

int n, c;
int a[N], b[N];
Node stree[4 * N];

void build(int id, int l, int r) {
    if(l == r) {
        stree[id].set(1, a[l] % MOD);
        stree[id].set(0, b[l] % MOD);
    } else {
        int chld = id << 1;
        int m = (l + r) / 2;

        build(chld, l, m);
        build(chld+1, m+1, r);

        stree[id] = stree[chld] + stree[chld+1];
    }
}

void update(int id, int l, int r, int x) {
    if(l == r) {
        stree[id].set(1, a[l] % MOD);
        stree[id].set(0, b[l] % MOD);
    } else {
        int chld = id << 1;
        int m = (l + r) / 2;

        if(x <= m)  update(chld, l, m, x);
        else        update(chld+1, m+1, r, x);

        stree[id] = stree[chld] + stree[chld+1];
    }
}

void read() {
    scanf("%d %d", &n, &c);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &b[i]);
    }
}

void work() {
    build(1, 1, n);

    int q; scanf("%d", &q);

    for(int i = 0 ; i < q ; i++) {
        int idx, ap, bp;
        scanf("%d %d %d", &idx, &ap, &bp);

        a[idx] = ap;
        b[idx] = bp;

        update(1, 1, n, idx);

        printf("%d\n", stree[1].get_at_least(c));
    }
}

int main() {
    read();
    work();
    return 0;
}