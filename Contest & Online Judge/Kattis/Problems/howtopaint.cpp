#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e5 + 3;
const int N = 1005;

int modPow(int base, int po) {
    int ret = 1;
    while (po) {
        if (po & 1) ret = 1ll * ret * base % MOD;
        base = 1ll * base * base % MOD;
        po >>= 1;
    }
    return ret;
}

struct ModInt {
    int pwr;
    int val;

    ModInt() {
        pwr = 0;
        val = 1;
    }

    ModInt(int x) {
        pwr = 0;
        while (x % MOD == 0) {
            pwr++;
            x /= MOD;
        }
        val = x;
    }

    ModInt(int x, int y) {
        pwr = x, val = y;
    }

    ModInt operator *(ModInt other) const {
        return ModInt(pwr + other.pwr, 1ll * val * other.val % MOD); 
    }

    ModInt operator /(ModInt other) const {
        return ModInt(pwr - other.pwr, 1ll * val * modPow(other.val, MOD-2) % MOD);
    }

    void print() {
        printf("%d %d\n", pwr, val);
    }
};

bool flag[N][N];
int cnt[N][N];
int arr[N];
int n, m;

void read() {
    scanf("%d %d", &m, &n);
    for (int i = 1 ; i <= m ; i++)
        scanf("%d", &arr[i]);
}

void prepare() {
    for (int i = 1 ; i <= n ; i++)
        for (int j = 1 ; j <= m ; j++)
            if (arr[j] >= n-i+1) {
                flag[i][j] = 1;
            }
}

ModInt calcBlue() {
    memset(cnt, 0, sizeof cnt);

    int tot = 0;
    ModInt num(1), denom(1);

    for (int i = 1 ; i <= n ; i++) {
        int blue = 0;
        for (int j = m ; j >= 1 ; j--) {
            if (flag[i][j]) {
                blue++;
                cnt[i][j] += blue;
            }
        }
    }
    for (int j = 1 ; j <= m ; j++) {
        int blue = 0;
        for (int i = 1 ; i <= n ; i++) {
            if (flag[i][j]) {
                blue++;
                cnt[i][j] += (blue-1);
            }
        }
    }

    for (int i = 1 ; i <= n ; i++)
        for (int j = 1 ; j <= m ; j++)
            if (flag[i][j]) {
                tot++;
                num = num * ModInt(tot);
                denom = denom * ModInt(cnt[i][j]);
            }

    num = num / denom;
    return num;
}

ModInt calcRed() {
    memset(cnt, 0, sizeof cnt);

    int tot = 0;
    ModInt num(1), denom(1);

    for (int i = 1 ; i <= n ; i++) {
        int red = 0;
        for (int j = 1 ; j <= m ; j++) {
            if (!flag[i][j]) {
                red++;
                cnt[i][j] += red;
            }
        }
    }
    for (int j = 1 ; j <= m ; j++) {
        int red = 0;
        for (int i = n ; i >= 1 ; i--) {
            if (!flag[i][j]) {
                red++;
                cnt[i][j] += (red-1);
            }
        }
    }

    for (int i = 1 ; i <= n ; i++)
        for (int j = 1 ; j <= m ; j++)
            if (!flag[i][j]) {
                tot++;
                num = num * ModInt(tot);
                denom = denom * ModInt(cnt[i][j]);
            }

    num = num / denom;
    return num;
}

ModInt calcPartition() {
    int blue = 0;
    for (int i = 1 ; i <= n ; i++)
        for (int j = 1 ; j <= m ; j++)
            blue += flag[i][j];
    int all = n * m;
    int red = all - blue;

    all -= 2;
    red--;
    blue--;

    ModInt num(1), denom(1);
    for (int i = 1 ; i <= all ; i++) num = num * ModInt(i);
    for (int i = 1 ; i <= blue ; i++) denom = denom * ModInt(i);
    for (int i = 1 ; i <= red ; i++) denom = denom * ModInt(i);

    num = num / denom;
    return num;
}

int main() {
    read();
    prepare();
    ModInt a = calcBlue();
    ModInt b = calcRed();
    ModInt c = calcPartition();

    ModInt ret = a;
    ret = ret * b;
    ret = ret * c;

    // a.print();
    // b.print();
    // c.print();
    ret.print();
    return 0;
}
