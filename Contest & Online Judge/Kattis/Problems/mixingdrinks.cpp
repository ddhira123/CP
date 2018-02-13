#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int maks[N];
int stree[4*N];
int psum[N];
int dp[N];

int n, m;

void build(int id, int l, int r) {
    if(l == r) {
        stree[id] = maks[l];
    } else {
        int m = (l + r) / 2;
        int chld = id << 1;

        build(chld, l, m);
        build(chld+1, m+1, r);
        stree[id] = max(stree[chld], stree[chld+1]);
    }
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

int get_best(int r) {
    int lo = 1, hi = r;

    while(lo < hi) {
        int mid = (lo + hi) / 2;

        if(query(1, 1, n, mid, r) >= mid) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    return lo;
}

int get_sum(int l, int r) {
    int ret = psum[r];

    if(l > 0) {
        ret  = (ret - psum[l-1] + MOD) % MOD;
    }

    return ret;
}

void read() {
    scanf("%d %d", &n, &m);
    for(int i = 0 ; i < m ; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        if(a > b) swap(a, b);
        maks[b] = max(maks[b], a);
    }
}

int work() {
    build(1, 1, n);
    dp[0] = 1;
    psum[0] = 1;

    for(int i = 1 ; i <= n ; i++) {
        int l = get_best(i);

        dp[i] = get_sum(l-1, i-1);
        psum[i] = (psum[i-1] + dp[i]) % MOD;
    }

    return dp[n];
}

int main() {
    read();
    printf("%d\n", work());
    return 0;
}