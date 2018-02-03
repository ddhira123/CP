#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

struct SegmentTree {
    int stree[4 * N];

    SegmentTree() {}

    void update(int id, int l, int r, int x, int val) {
        if(l == r) {
            stree[id] = val;
        } else {
            int m = (l + r) / 2;
            int chld = id << 1;

            if(x <= m)  update(chld, l, m, x, val);
            else        update(chld+1, m+1, r, x, val);

            stree[id] = min(stree[chld], stree[chld+1]);
        }
    }

    int query(int id, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            return stree[id];
        } else {
            int m = (l + r) / 2;
            int chld = id << 1;

            int ret = N;
            if(x <= m)  ret = min(ret, query(chld, l, m, x, y));
            if(y > m)   ret = min(ret, query(chld+1, m+1, r, x, y));

            return ret;
        }
    }
};

SegmentTree kiri, kanan;

int x[N], r[N];
int x_sorted[N];
pair<int, int> arr[N];
int n;

int mins[N], maks[N];

void read() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d %d", &x[i], &r[i]);
    }
}

void prepare() {
    for(int i = 0 ; i < n ; i++) {
        x_sorted[i] = x[i];
        arr[i] = {x[i], r[i]};
    }

    sort(x_sorted, x_sorted + n);
    sort(arr, arr + n);

    for(int i = 0 ; i < n ; i++) {
        mins[i] = lower_bound(x_sorted, x_sorted + n, arr[i].first - arr[i].second) - x_sorted;
        maks[i] = upper_bound(x_sorted, x_sorted + n, arr[i].first + arr[i].second) - x_sorted - 1;
        maks[i] = -maks[i];

        kiri.update(1, 0, n-1, i, mins[i]);
        kanan.update(1, 0, n-1, i, maks[i]);
    }
}

void work() {
    bool change = true;
    while(change) {
        change = false;

        for(int i = 0 ; i < n ; i++) {
            int l = mins[i];
            int r = -maks[i];

            int cur_l = kiri.query(1, 0, n-1, l, r);
            int cur_r = kanan.query(1, 0, n-1, l, r);

            if(cur_l != l) {
                mins[i] = cur_l;
                kiri.update(1, 0, n-1, i, mins[i]);
                change = true;
            }
            if(cur_r != -r) {
                maks[i] = cur_r;
                kanan.update(1, 0, n-1, i, maks[i]);
                change = true;
            }
        }

        for(int i = n-1 ; i >= 0 ; i--) {
            int l = mins[i];
            int r = -maks[i];

            int cur_l = kiri.query(1, 0, n-1, l, r);
            int cur_r = kanan.query(1, 0, n-1, l, r);

            if(cur_l != l) {
                mins[i] = cur_l;
                kiri.update(1, 0, n-1, i, mins[i]);
                change = true;
            }
            if(cur_r != -r) {
                maks[i] = cur_r;
                kanan.update(1, 0, n-1, i, maks[i]);
                change = true;
            }
        }
    }

    for(int i = 0 ; i < n ; i++) {
        int idx = lower_bound(x_sorted, x_sorted + n, x[i]) - x_sorted;
        int ret = -maks[idx] - mins[idx] + 1;
        printf("%d%c", ret, i+1 == n ? '\n' : ' ');
    }
}

int main() {
    read();
    prepare();
    work();
    return 0;
}