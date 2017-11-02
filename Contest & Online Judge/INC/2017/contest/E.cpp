#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

struct Node {
    int lazy;
    int l[2], r[2], maks[2];
    int len;

    Node operator +(Node other) const {
        Node ret;

        ret.lazy = 0;
        ret.len = len + other.len;

        for(int i = 0 ; i < 2 ; i++) {
            ret.l[i] = l[i];
            if(l[i] == len) {
                ret.l[i] += other.l[i];
            }

            ret.r[i] = other.r[i];
            if(other.r[i] == other.len) {
                ret.r[i] += r[i];
            }

            ret.maks[i] = max(maks[i], other.maks[i]);
            ret.maks[i] = max(ret.maks[i], r[i] + other.l[i]);
        }

        return ret;
    }

    void flip() {
        lazy ^= 1;

        swap(l[0], l[1]);
        swap(r[0], r[1]);
        swap(maks[0], maks[1]);
    }
};

char s[N];
int n, q;
Node stree[4 * N];

void propagate(int id) {
    if(stree[id].lazy == 0) return;

    for(int i = 0 ; i < 2 ; i++) {
        int chld = id << 1;
        stree[chld + i].flip();
    }

    stree[id].lazy = 0;
}

void build(int id, int l, int r) {
    stree[id].len = r - l + 1;

    if(l == r) {
        int val = s[l] - '0';
        stree[id].l[val] = 1;
        stree[id].r[val] = 1;
        stree[id].maks[val] = 1;
    } else {
        int chld = id << 1;
        int m = (l + r) / 2;

        build(chld, l, m);
        build(chld+1, m+1, r);

        stree[id] = stree[chld] + stree[chld+1];
    }
}

void update(int id, int l, int r, int x, int y) {
    if(x <= l && r <= y) {
        stree[id].flip();
    } else {
        int chld = id << 1;
        int m = (l + r) / 2;

        propagate(id);
        if(x <= m)  update(chld, l, m, x, y);
        if(y > m)   update(chld+1, m+1, r, x, y);

        stree[id] = stree[chld] + stree[chld+1];
    }
}

Node query(int id, int l, int r, int x, int y) {
    if(x <= l && r <= y) {
        return stree[id];
    } else {
        int chld = id << 1;
        int m = (l + r) / 2;

        propagate(id);
        Node res;

        if(x <= m && y > m) {
            res = query(chld, l, m, x, y);
            res = res + query(chld+1, m+1, r, x, y);
        } else if(x <= m) {
            res = query(chld, l, m, x, y);
        } else {
            res = query(chld+1, m+1, r, x, y);
        }

        stree[id] = stree[chld] + stree[chld+1];

        return res;
    }
}

void init() {
    scanf("%d %d", &n, &q);
    scanf("%s", s);

    build(1, 0, n-1);
}

void work() {
    for(int i = 0 ; i < q ; i++) {
        int opt, l, r;
        scanf("%d %d %d", &opt, &l, &r);
        l--; r--;

        if(opt == 1) {
            update(1, 0, n-1, l, r);
        } else {
            Node ret = query(1, 0, n-1, l, r);

            int ans = max(ret.maks[0], ret.maks[1]);

            printf("%d\n", ans);
        }
    }
}

int main() {
    init();
    work();
    return 0;
}