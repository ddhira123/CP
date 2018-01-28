#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e5 + 5;
const string STR = "PPAP";

struct Matrix {
    int mat[4][4];

    Matrix() {
        memset(mat, 0, sizeof mat);
    }

    Matrix operator *(Matrix other) const {
        Matrix ret;

        for(int i = 0 ; i < 4 ; i++) {
            for(int j = i ; j < 4 ; j++)
                for(int k = j+1 ; k < 4 ; k++) {
                    ret.mat[i][k] = (ret.mat[i][k] + 1ll * mat[i][j] * other.mat[j+1][k]) % MOD;
                }
        }

        for(int i = 0 ; i < 4 ; i++)
            for(int j = 0 ; j < 4 ; j++) {
                ret.mat[i][j] = (ret.mat[i][j] + mat[i][j]) % MOD;
                ret.mat[i][j] = (ret.mat[i][j] + other.mat[i][j]) % MOD;
            }

        return ret;
    }

    Matrix operator ^(int po) const {
        Matrix ret;
        Matrix base;

        for(int i = 0 ; i < 4 ; i++) {
            for(int j = 0 ; j < 4 ; j++) {
                base.mat[i][j] = mat[i][j];
            }
        }

        while(po) {
            if(po & 1) ret = ret * base;
            base = base * base;
            po >>= 1;
        }

        return ret;
    }
};

int n, k;
string s;

int dp[N][4][4];

int solve(int now, int l, int r) {
    if(now == s.length()) return 0;
    int &ret = dp[now][l][r];

    if(ret != -1) return ret;
    ret = solve(now+1, l, r);

    if(s[now] == STR[l]) {
        if(l == r) {
            ret = (ret + 1) % MOD;
        } else {
            ret = (ret + solve(now+1, l+1, r)) % MOD;
        }
    }

    return ret;
}

void read() {
    cin >> n >> k;
    cin >> s;
}

void work() {
    memset(dp, -1, sizeof dp);

    Matrix m;
    for(int i = 0 ; i < 4 ; i++) {
        for(int j = i ; j < 4 ; j++)
            m.mat[i][j] = solve(0, i, j);
    }

    m = m^n;

    cout << m.mat[0][3] << endl;
}

int main() {
    read();
    work();
    return 0;
}