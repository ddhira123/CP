#include <bits/stdc++.h>
using namespace std;

struct data {
    int idx;
    int sign;
    long long val;
};

const int N = 1e5 + 5;

long long dp[64][1024];
bool vis[64][1024];
long long sums[64];

int base;
vector<data> que[11];
int n;
long long ans[N];

long long solve(int sisa, int mask, bool flag = false) {
    if(sisa == 0) {
        return mask == 0;
    }

    long long &ret = dp[sisa][mask];
    if(vis[sisa][mask]) {
        return ret;
    }

    vis[sisa][mask] = true;
    ret = 0;
    for(int i = 0 ; i < base ; i++) {
        ret += solve(sisa - 1, mask ^ (1 << i));
    }

    return ret;
}

long long calc(long long x) {
    if(x == 0) {
        return 0;
    }

    vector<int> v;
    while(x > 0) {
        v.push_back(x % base);
        x /= base;
    }

    // cout << "DONE prep\n";
    long long ret = 0;
    // highest beda
    ret = sums[v.size() - 1];
    // cout << ret << " " << v.size() << endl;
    int mask = 0;
    for(int i = v.size()-1 ; i >= 0 ; i--) {
        int st = i+1 == v.size() ? 1 : 0;

        for(int j = st ; j < v[i] ; j++) {
            int nmask = mask ^ (1 << j);

            // cout << "calling " << i << " " << nmask << endl;
            ret += solve(i, nmask, true);
        }

        mask ^= (1 << v[i]);
    }

    ret += (mask == 0);
    return ret;
}

int get_max(int base) {
    long long mx = 1e18;
    int iter = 0;

    while(mx) {
        mx /= base;
        iter++;
    }

    return iter;
}

void read() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        int base;
        long long l, r;

        scanf("%d %lld %lld", &base, &l, &r);
        que[base].push_back((data){i, -1, l-1});
        que[base].push_back((data){i, 1, r});
    }
}

void work() {
    for(int i = 2 ; i <= 10 ; i++) {
        memset(vis, false, sizeof vis);
        base = i;

        // cout << base << endl;
        for(int i = 1 ; i <= get_max(base) ; i++) {
            sums[i] = sums[i-1];
            for(int j = 1 ; j < base ; j++)
                sums[i] += solve(i-1, 1 << j);
        }
        // cout << "done\n";

        for(data it : que[i]) {
            int idx = it.idx;
            int sign = it.sign;
            long long val = it.val;

            // cout << i << " " << idx << " " << sign << " " << val << endl;

            long long ret = sign * calc(val);
            ans[idx] += ret;
        }
        // cout << "kelar\n";
    }

    for(int i = 0 ; i < n ; i++) {
        printf("%lld\n", ans[i]);
    }
}

int main() {
    read();
    work();
    return 0;
}