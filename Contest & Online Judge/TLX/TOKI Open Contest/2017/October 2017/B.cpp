#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct Matrix {
    int mat[3][3];

    Matrix() {
        memset(mat, 0, sizeof mat);
    }

    Matrix operator *(Matrix other) const {
        Matrix res;
        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                for(int k = 0 ; k < 3 ; k++)
                    res.mat[i][j] = (res.mat[i][j] + 1ll * mat[i][k] * other.mat[k][j]) % MOD;
        return res;
    }

    Matrix operator ^(int po) const {
        Matrix res;
        Matrix base;

        for(int i = 0 ; i < 3 ; i++) {
            res.mat[i][i] = 1;
            for(int j = 0 ; j < 3 ; j++)
                base.mat[i][j] = mat[i][j];
        }

        while(po) {
            if(po & 1) res = res * base;
            base = base * base;
            po >>= 1;
        }

        return res;
    }
};

int get(int x) {
    if(x == 1) return 1;
    if(x == 2) return 2;
    Matrix ret;
    ret.mat[0][0] = ret.mat[0][1] = ret.mat[0][2] = 1;
    ret.mat[1][0] = 1;
    ret.mat[2][2] = 1;

    ret = ret^(x-2);

    long long res = 2ll * ret.mat[0][0] + 1ll * ret.mat[0][1] + ret.mat[0][2];
    res %= MOD;

    // cout << x << " " << res << endl;

    return res;
}

int main() {
    int n; cin >> n;
    int ret = get(n+1) - get(n);
    if(ret < 0) ret += MOD;
    cout << ret << endl;
    return 0;
}