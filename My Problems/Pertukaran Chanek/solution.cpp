#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 1e5 + 5;
const int Q = 1e5 + 5;

vector<pair<int, LL>> opt[N];
vector<pair<int,int>> queries[N];
LL psum[N];
LL stree[4 * N];
LL ans[N];

int n, k, q;
int arr[N];
int ql[Q], qr[Q];

void build(int id, int l, int r) {
    stree[id] = 0;
    if(l < r) {
        int chld = id << 1;
        int m = (l + r) / 2;

        build(chld, l, m);
        build(chld+1, m+1, r);
    }
}

void update(int id, int l, int r, int x, LL val) {
    if(l == r) {
        stree[id] = max(stree[id], val);
    } else {
        int m = (l + r) / 2;
        int chld = id << 1;

        if(x <= m) update(chld, l, m, x, val);
        else       update(chld+1, m+1, r, x, val);

        stree[id] = max(stree[chld], stree[chld+1]);
    }
} 

LL query(int id, int l, int r, int x, int y) {
    if(x <= l && r <= y) {
        return stree[id];
    } else {
        int m = (l + r) / 2;
        int chld = id << 1;

        LL ret = 0;
        if(x <= m)  ret = max(ret, query(chld, l, m, x, y));
        if(y > m)   ret = max(ret, query(chld+1, m+1, r, x, y));

        return ret;
    }
}

void read() {
    scanf("%d %d %d", &n, &k, &q);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", arr + i);
    }
    for(int i = 1 ; i <= q ; i++) {
        scanf("%d %d", ql + i, qr + i);
    }
}

void prepare() {
    // prefix sum
    for(int i = 1 ; i <= n ; i++) {
        psum[i] = psum[i-1] + arr[i];
    }

    // make opt using stack
    vector<pair<int,int>> stek;
    for(int i = 1 ; i <= n ; i++) {
        pair<int, int> cur = {arr[i], i};

        while(!stek.empty()) {
            int idx = stek.back().second;

            if(i - idx <= k) {
                LL mx = max(arr[idx], arr[i]);
                LL mn = min(arr[idx], arr[i]);
                LL val = psum[i-1] - psum[idx];

                val += k * mx;
                val += (k - (i-1 - idx)) * mn;

                opt[idx].push_back({i, val});
            }

            if(cur >= stek.back()) {
                stek.pop_back();
            } else {
                break;
            }
        }

        stek.push_back(cur);
    }

    // make queries
    for(int i = 1 ; i <= q ; i++) {
        queries[ql[i]].push_back({qr[i], i});
    }

    // reset segment tree
    build(1, 1, n);
}

void work() {
    for(int i = n ; i >= 1 ; i--) {
        for(pair<int, LL> upd : opt[i]) {
            update(1, 1, n, upd.first, upd.second);
        }

        for(pair<int,int> qu : queries[i]) {
            ans[qu.second] = query(1, 1, n, i, qu.first);
        }

        queries[i].clear();
        opt[i].clear();
    }

    for(int i = 1 ; i <= q ; i++) {
        printf("%lld\n", ans[i]);
    }
}

int main() {
    int t;
    scanf("%d", &t);

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        prepare();
        work();
    }
    return 0;
}