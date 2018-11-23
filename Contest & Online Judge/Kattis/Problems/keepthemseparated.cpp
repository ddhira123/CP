#include <bits/stdc++.h>
using namespace std;

const int MX = 5005;
const int MOD = 1e9 + 7;
const int N = 1e5 + 5;

int modPow(int base, int po) {
    int ret = 1;
    while (po) {
        if (po & 1) ret = 1ll * ret * base % MOD;
        base = 1ll * base * base % MOD;
        po >>= 1;
    }
    return ret;
}

struct Rectangle {
    int r1, c1;
    int r2, c2;

    void read() {
        scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
        // assert(r1 < r2);
        if (r1 < r2) {
            swap(r1, r2);
        }
        if (c1 < c2) {
            swap(c1, c2);
        }
    }
};

int BIT[MX][MX];
Rectangle rect[N];

void update(int r, int c, int val) {
    for (int i = r ; i < MX ; i += i & -i)
        for (int j = c ; j < MX ; j += j & -j)
            BIT[i][j] = (BIT[i][j] + val) % MOD;
}

int query(int r, int c) {
    int ret = 0;
    for (int i = r ; i > 0 ; i -= i & -i)
        for (int j = c ; j > 0 ; j -= j & -j)
            ret = (ret + BIT[i][j]) % MOD;
    return ret;
}

void updater(Rectangle a, int val) {
    update(a.r1, a.c1, val);
    update(a.r2+1, a.c1, MOD-val);
    update(a.r1, a.c2+1, MOD-val);
    update(a.r2+1, a.c2+1, val);
}

int main() {
    int n; scanf("%d", &n);

    string ret = "";
    for (int i = 1 ; i <= n ; i++) {
        // cerr << i << endl;
        int opt; scanf("%d", &opt);

        if (opt == 1) {
            rect[i].read();

            int val = modPow(2, i);
            updater(rect[i], val);
        } else if (opt == 2) {
            int j; scanf("%d", &j);

            int val = modPow(2, j);
            updater(rect[j], MOD-val);
        } else {
            int a, b, c, d;
            scanf("%d %d %d %d", &a, &b, &c, &d);

            int hsh1 = query(a, b);
            int hsh2 = query(c, d);

            if (hsh1 == hsh2) ret += "Y";
            else ret += "N";
        }
    }

    cout << ret << endl;
    return 0;
}