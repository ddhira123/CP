#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const long long NO_SET = 4e18;

long long s_max[4 * N];
long long s_min[4 * N];
long long lazy_set[4 * N];
long long lazy_add[4 * N];

int arr[N];
int n, q;

void build(int id, int l, int r) {
    lazy_set[id] = NO_SET;

    if(l == r) {
        s_max[id] = 0;
        s_min[id] = 0;
    } else {
        int chld = id << 1;
        int m = (l + r) / 2;

        build(chld, l, m);
        build(chld + 1, m + 1, r);

        s_min[id] = min(s_min[chld], s_min[chld+1]);
        s_max[id] = max(s_max[chld], s_max[chld+1]);
    }
}

void propagate(int id) {
    int chld = id << 1;

    if(lazy_set[id] == NO_SET) {
        for(int i = 0 ; i < 2 ; i++) {
            s_max[chld+i] += lazy_add[id];
            s_min[chld+i] += lazy_add[id];

            if(lazy_set[chld+i] == NO_SET) {
                lazy_add[chld+i] += lazy_add[id];
            } else {
                lazy_set[chld+i] += lazy_add[id];
            }
        }
    } else {
        for(int i = 0 ; i < 2 ; i++) {
            s_max[chld+i] = lazy_set[id];
            s_min[chld+i] = lazy_set[id];
            lazy_set[chld+i] = lazy_set[id];
            lazy_add[chld+i] = 0;
        }
    }

    lazy_set[id] = NO_SET;
    lazy_add[id] = 0;
}

void update_sum(int id, int l, int r, int x, int y, int val) {
    if(x <= l && r <= y) {
        s_max[id] += val;
        s_min[id] += val;

        if(lazy_set[id] == NO_SET) {
            lazy_add[id] += val;
        } else {
            lazy_set[id] += val;
        }
    } else {
        int chld = id << 1;
        int m = (l + r) / 2;

        propagate(id);
        if(x <= m)  update_sum(chld, l, m, x, y, val);
        if(y > m)   update_sum(chld+1, m+1, r, x, y, val);

        s_min[id] = min(s_min[chld], s_min[chld+1]);
        s_max[id] = max(s_max[chld], s_max[chld+1]);
    }
}

void update_min(int id, int l, int r, int x, int y, int val) {
    // cout << id << " " << l << " " << r << " " << x << " " << y << " " << val << endl;
    if(s_max[id] <= val) {
        return;
    }

    if(x <= l && r <= y) {
        if(s_min[id] >= val) {
            s_min[id] = val;
            s_max[id] = val;
            lazy_set[id] = val;
            lazy_add[id] = 0;

            return;
        }

        if(l == r) {
            return;
        }
    }

    int chld = id << 1;
    int m = (l + r) / 2;

    propagate(id);
    if(x <= m)  update_min(chld, l, m, x, y, val);
    if(y > m)   update_min(chld+1, m+1, r, x, y, val);

    s_min[id] = min(s_min[chld], s_min[chld+1]);
    s_max[id] = max(s_max[chld], s_max[chld+1]);
}

void update_max(int id, int l, int r, int x, int y, int val) {
    if(s_min[id] >= val) {
        return;
    }

    if(x <= l && r <= y) {
        if(s_max[id] <= val) {
            s_min[id] = val;
            s_max[id] = val;
            lazy_set[id] = val;
            lazy_add[id] = 0;

            return;
        }

        if(l == r) {
            return;
        }
    }

    int chld = id << 1;
    int m = (l + r) / 2;

    propagate(id);
    if(x <= m)  update_max(chld, l, m, x, y, val);
    if(y > m)   update_max(chld+1, m+1, r, x, y, val);

    s_min[id] = min(s_min[chld], s_min[chld+1]);
    s_max[id] = max(s_max[chld], s_max[chld+1]);
}

void drop(int id, int l, int r) {
    if(l == r) {
        printf("%lld%c", s_min[id], l == n ? '\n' : ' ');
    } else {
        int chld = id << 1;
        int m = (l + r) / 2;

        propagate(id);
        drop(chld, l, m);
        drop(chld+1, m+1, r);
    }
}

void read() {
    scanf("%d %d", &n, &q);
}

void prepare() {
    build(1, 1, n);
}

void work() {
    for(int i = 0 ; i < q ; i++) {
        int opt, l, r, v;
        scanf("%d %d %d %d", &opt, &l, &r, &v);

        if(opt == 1) {
            update_sum(1, 1, n, l, r, v);
        } else if(opt == 2) {
            update_max(1, 1, n, l, r, v);
        } else {
            update_min(1, 1, n, l, r, v);
        }

        // drop(1, 1, n);
    }

    drop(1, 1, n);
}

int main() {
    read();
    prepare();
    work();
    return 0;
}