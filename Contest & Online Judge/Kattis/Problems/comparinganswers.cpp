#include <bits/stdc++.h>
using namespace std;

const int TRIAL = 10;

struct Matrix {
    vector<vector<int>> v;

    Matrix(int n = 0, int m = 0) {
        v = vector<vector<int>>(n, vector<int>(m));
    }

    void random_binary() {
        for(vector<int> &row : v) {
            for(int &col : row) {
                col = rand() & 1;
            }
        }
    }

    void read(int n, int m) {
        v = vector<vector<int>>(n, vector<int>(m));

        for(vector<int> &row : v) {
            for(int &col : row) {
                scanf("%d", &col);
            }
        }
    }

    Matrix operator *(Matrix other) const {
        Matrix ret(v.size(), other.v[0].size());

        for(int i = 0 ; i < v.size() ; i++) {
            for(int j = 0 ; j < other.v[0].size() ; j++) {
                for(int k = 0 ; k < v[0].size() ; k++) {
                    ret.v[i][j] += v[i][k] * other.v[k][j];
                }
            }
        }

        return ret;
    }

    void print() {
        puts("=========");
        for(vector<int> row : v) {
            for(int x : row) {
                printf("%d ", x);
            }
            puts("");
        }
        puts("=========");
    }

    bool operator ==(Matrix other) const {
        return v == other.v;
    }

    bool operator !=(Matrix other) const {
        return v != other.v;
    }
};

Matrix a, a_sqr;
int n;

bool read() {
    scanf("%d", &n);
    if(n == 0) {
        return false;
    }

    a.read(n, n);
    a_sqr.read(n, n);

    return true;
}

bool work() {
    for(int trial = 0 ; trial < TRIAL ; trial++) {
        Matrix dummy(n, 1);
        dummy.random_binary();

        Matrix rhs = a_sqr * dummy;
        Matrix lhs = a * dummy;
        lhs = a * lhs;

        if(lhs != rhs) {
            return false;
        }
    }

    return true;
}

int main() {
    while(read()) {
        printf("%s\n", work() ? "YES" : "NO");
    }
    return 0;
}