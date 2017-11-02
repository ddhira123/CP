#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e5 + 5;

struct Matrix {
    int mat[3][3];

    Matrix() {
        memset(mat, 0, sizeof mat);
    }

    Matrix(int n, int a, int b) {
        if(a != b) {
            mat[0][0] = 0;
            mat[0][1] = n-2;
            mat[0][2] = 1;

            mat[1][0] = 1;
            mat[1][1] = max(n-3, 0);
            mat[1][2] = 1;

            mat[2][0] = 1;
            mat[2][1] = n-2;
            mat[2][2] = 0;
        } else {
            mat[0][0] = 0;
            mat[0][1] = n-1;
            mat[0][2] = 0;

            mat[1][0] = 1;
            mat[1][1] = max(n-2, 0);
            mat[1][2] = 0;

            mat[2][0] = 0;
            mat[2][1] = 0;
            mat[2][2] = 0;
        }
    }

    Matrix operator *(Matrix other) const{
        Matrix ret;

        for(int i = 0 ; i < 3 ; i++)
            for(int j = 0 ; j < 3 ; j++)
                for(int k = 0 ; k < 3 ; k++) {
                    ret.mat[i][j] = (ret.mat[i][j] + 1ll * mat[i][k] * other.mat[k][j]) % MOD;
                }

        return ret;
    }

    Matrix operator ^(long long pwr) const {
        Matrix ret;
        Matrix base;

        for(int i = 0 ; i < 3 ; i++) {
            ret.mat[i][i] = 1;
            for(int j = 0 ; j < 3 ; j++) {
                base.mat[i][j] = mat[i][j];
            }
        }

        while(pwr) {
            if(pwr & 1) ret = ret * base;
            base = base * base;
            pwr >>= 1;
        }

        return ret;
    }
};

int n, k;
long long m;
long long day[N];
int tipe[N];

int main() {
    scanf("%d %lld %d", &n, &m, &k);
    for(int i = 0 ; i < k ; i++) {
        scanf("%lld %d", &day[i], &tipe[i]);
    }

    long long ret = 1;

    if(day[0] != 1) {
        long long ways = 0;
        int a;
        int b;
        long long len = day[0] - 1;
        Matrix cur;

        // pasang pertama = day[0]
        a = tipe[0];
        b = tipe[0];
        cur = Matrix(n, a, b);
        cur = cur^len;

        ways = (ways + cur.mat[0][0]) % MOD;

        // pasang pertama != day[0]
        a = -1;
        b = tipe[0];
        cur = Matrix(n, a, b);
        cur = cur^len;

        ways = (ways + 1ll * (n-1) * cur.mat[0][2]) % MOD;

        ret = ret * ways % MOD;       
    }

    for(int i = 1 ; i < k ; i++) {
        int a = tipe[i-1];
        int b = tipe[i];
        long long len = day[i] - day[i-1];

        Matrix cur = Matrix(n, a, b);
        cur = cur^len;

        if(a != b) {
            ret = ret * cur.mat[0][2] % MOD;
        } else {
            ret = ret * cur.mat[0][0] % MOD;
        }
    }

    if(day[k-1] != m) {
        long long ways = 0;
        int a;
        int b;
        long long len = m - day[k-1];
        Matrix cur;

        // pasang akhir = day[k-1]
        a = tipe[k-1];
        b = tipe[k-1];
        cur = Matrix(n, a, b);
        cur = cur^len;

        ways = (ways + cur.mat[0][0]) % MOD;

        // pasang akhir != day[k-1]
        a = tipe[k-1];
        b = -1;
        cur = Matrix(n, a, b);
        cur = cur^len;

        ways = (ways + 1ll * (n-1) * cur.mat[0][2]) % MOD;

        ret = ret * ways % MOD;       
    }

    printf("%lld\n", ret);
    return 0;
}