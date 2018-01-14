#include <bits/stdc++.h>
using namespace std;

const int MAGIC = 500;
const int MX = 2e5 + 5;

long long ans[MAGIC];

int occ_psum[MX];
long long norm_psum[MX];
long long sq_psum[MX];

int cnt[MX];
int n, q;

long long get_ans(int x) {
    long long ret = 0;

    for(int i = 0 ; i < MX ; i += x) {
        int r = min(MX-1, i + x - 1);

        int occ = occ_psum[r];
        long long norm = norm_psum[r];
        long long sq = sq_psum[r];

        if(i) {
            occ -= occ_psum[i-1];
            norm -= norm_psum[i-1];
            sq -= sq_psum[i-1];
        }

        ret += sq;
        ret -= 2ll * i * norm;
        ret += 1ll * i * i * occ;
    }

    return ret;
}

void read() {
    scanf("%d %d", &n, &q);
    for(int i = 0 ; i < n ; i++) {
        int x; scanf("%d", &x);
        cnt[x]++;
    }
}


void prepare() {
    for(int i = 1 ; i < MX ; i++) {
        occ_psum[i] = occ_psum[i-1] + cnt[i];
        norm_psum[i] = norm_psum[i-1] + 1ll * i * cnt[i];
        sq_psum[i] = sq_psum[i-1] + 1ll * i * i * cnt[i];
    }
}

void work() {
    for(int i = 1 ; i < MAGIC ; i++) {
        ans[i] = get_ans(i);
    }

    // int q; scanf("%d", &q);

    for(int i = 0 ; i < q ; i++) {
        int x; scanf("%d", &x);

        if(x < MAGIC) {
            printf("%lld\n", ans[x]);
        } else {
            printf("%lld\n", get_ans(x));
        }
    }
}

void reset() {
    memset(cnt, 0, sizeof cnt);
}

int main() {
    int t; scanf("%d", &t);

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        prepare();
        work();

        reset();
    }
    return 0;
}