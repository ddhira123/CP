#include <bits/stdc++.h>
using namespace std;

const int MAX_DIFFERENT = 17;
const int N = 1e5 + 5;

struct SegmentTree {
    int stree[4 * N];
    int n;

    SegmentTree() {
        memset(stree, 0, sizeof stree);
    }

    void set_n(int _n) {
        n = _n;
    }

    void update(int id, int l, int r, int x, int val) {
        if(l == r) {
            stree[id] = val;
        } else {
            int m = (l + r) / 2;
            int chld = id << 1;

            if(x <= m)  update(chld, l, m, x, val);
            else        update(chld+1, m+1, r, x, val);

            stree[id] = max(stree[chld], stree[chld+1]);
        }
    }

    void update(int x, int val) {
        update(1, 1, n, x, val);
    }

    int query(int id, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            return stree[id];
        } else {
            int m = (l + r) / 2;
            int chld = id << 1;

            int ret = 0;
            if(x <= m)  ret = max(ret, query(chld, l, m, x, y));
            if(y > m)   ret = max(ret, query(chld+1, m+1, r, x, y));

            return ret;
        }
    }

    int query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

SegmentTree tree[MAX_DIFFERENT];
int order_p[N];
int isi[MAX_DIFFERENT];
int different_number;

int p[N], s[N];
int n, q;

long long query(int l, int r, int m) {
    vector<pair<int, int>> v;

    for(int i = 0 ; i < different_number ; i++) {
        int val = tree[i].query(l, r);

        if(val != 0) {
            v.push_back({val, isi[i]});
        }
    }

    sort(v.begin(), v.end(), [](pair<int, int> a, pair<int, int> b) {
        return 1ll * a.second * b.first < 1ll * b.second * a.first;
    });

    long long ret = 0;
    for(pair<int, int> x : v) {
        int price = x.second;
        int val = x.first;
        long long use = m / price;

        ret += use * val;
        m %= price;
    }

    return ret;
}

void update(int x, int val) {
    tree[order_p[x]].update(x, val);
}

void read() {
    scanf("%d %d", &n, &q);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", p + i);
    }
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", s + i);
    }
}

void prepare() {
    set<int> st;
    for(int i = 1 ; i <= n ; i++) {
        st.insert(p[i]);
    }

    map<int, int> num;
    
    for(int x : st) {
        num[x] = different_number;
        isi[different_number] = x;
        different_number++;
    }

    for(int i = 0 ; i < different_number ; i++) {
        tree[i].set_n(n);
    }

    for(int i = 1 ; i <= n ; i++) {
        order_p[i] = num[p[i]];
        tree[order_p[i]].update(i, s[i]);
    }
}

void work() {
    for(int i = 1 ; i <= q ; i++) {
        int opt; scanf("%d", &opt);

        if(opt == 1) {
            int l, r, m;
            scanf("%d %d %d", &l, &r, &m);

            printf("%lld\n", query(l, r, m));
        } else {
            int x, val;
            scanf("%d %d", &x, &val);

            update(x, val);
        }
    }
}

int main() {
    read();
    prepare();
    work();
    return 0;
}
