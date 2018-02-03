#include <bits/stdc++.h>
using namespace std;

const int MX = 55;
const int ALPHA = 26;

// long long mul(long long a, long long b, long long mod) {
//     return a * b % mod;
//     if(b == 0) return 0;
//     if(mod / b > a) return a * b;
//     if(b & 1) return (mul(a, b-1, mod) + a) % mod;
//     return (2 * mul(a, b / 2, mod)) % mod;
// }

inline long long mul(long long a, long long b, long long mod){
    long double res = a;
    res *= b;
    long long c = (long long)(res / mod);
    a *= b;
    a -= c * mod;
    a %= mod;
    if (a < 0)
        a += mod;
    return a;    
}

struct Matrix {
    int sz;
    long long mod;

    long long mat[MX][MX];

    Matrix(int _sz = 0, long long _mod = 0) {
        sz = _sz;
        mod = _mod;
        memset(mat, 0, sizeof mat);
    }

    Matrix operator *(Matrix other) const {
        Matrix ret(sz, mod);

        for(int i = 0 ; i < sz ; i++)
            for(int j = 0 ; j < sz ; j++)
                for(int k = 0 ; k < sz ; k++) {
                    ret.mat[i][j] = (ret.mat[i][j] + mul(mat[i][k], other.mat[k][j], mod)) % mod;
                }

        return ret;
    }

    Matrix operator ^(long long po) const {
        Matrix ret(sz, mod);
        Matrix base(sz, mod);

        for(int i = 0 ; i < sz ; i++) {
            ret.mat[i][i] = 1;
            for(int j = 0 ; j < sz ; j++) {
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

    void print() {
        cout << sz << " " << mod << endl;
        for(int i = 0 ; i < sz ; i++) {
            for(int j = 0 ; j < sz ; j++) {
                cout << i << " " << j << " -> " << mat[i][j] << endl;
            }
        }
    }
};

long long n, m;
string s;
int fail[MX];
int nxt[MX][ALPHA];
Matrix matrix;

void read() {
    cin >> n >> m;
    cin >> s;
}

void prepare() {
    memset(nxt, -1, sizeof nxt);
    fail[0] = 0;
    
    for(int i = 0 ; i < s.size() ; i++) {
        nxt[i][s[i] - 'a'] = i+1;

        for(int j = 0 ; j < ALPHA ; j++)
            if(j + 'a' != s[i]) {
                if(i == 0) nxt[i][j] = 0;
                else nxt[i][j] = nxt[fail[i]][j];
            }

        if(i == 0) fail[i+1] = 0;
        else fail[i+1] = nxt[fail[i]][s[i] - 'a'];
    }

    // for(int i = 0 ; i < s.size() ; i++)
    //     for(int j = 0 ; j < ALPHA ; j++)
    //         cout << "nxt " << i << " " << j << ": " << nxt[i][j] << endl;

    matrix = Matrix(s.size()+1, m);

    for(int i = 0 ; i < s.size() ; i++) {
        for(int j = 0 ; j < ALPHA ; j++) {
            matrix.mat[i][nxt[i][j]]++;
        }
    }

    matrix.mat[s.size()][s.size()] = ALPHA;
}

long long solve() {
    // matrix.print();
    matrix = matrix^n;
    // matrix.print();
    return matrix.mat[0][s.size()] % m;
}

int main() {
    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        prepare();
        cout << solve() << endl;
    }
    return 0;
}