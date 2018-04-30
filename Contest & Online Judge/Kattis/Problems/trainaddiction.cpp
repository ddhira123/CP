#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int K = 50;

struct Matrix {
  int mat[K][K];

  Matrix() {
    memset(mat, 0, sizeof mat);
  }

  Matrix operator *(Matrix other) const {
    Matrix ret;

    for(int i = 0 ; i < K ; i++) {
      for(int j = 0 ; j < K ; j++) {
        for(int k = 0 ; k < K ; k++) {
          ret.mat[i][j] = (ret.mat[i][j] + 1ll * mat[i][k] * other.mat[k][j]) % MOD;
        }
      }
    }

    return ret;
  }

  Matrix operator ^(int po) const {
    Matrix base;
    Matrix ret;

    for(int i = 0 ; i < K ; i++) {
      ret.mat[i][i] = 1;
      for(int j = 0 ; j < K ; j++) {
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

int dp[K+1];
int cnt[K+1];

int n, k;

Matrix m;

void read() {
  memset(cnt, 0, sizeof cnt);

  cin >> n >> k;
  for(int i = 0 ; i < k ; i++) {
    int x; cin >> x;
    cnt[x]++;
  }
}

void prepare() {
  dp[0] = 1;
  for(int i = 1 ; i <= K ; i++) {
    dp[i] = 0;
    for(int j = 1 ; j <= i ; j++) {
      dp[i] = (dp[i] + 1ll * cnt[j] * dp[i-j]) % MOD;
    }
  }

  m = Matrix();
  for(int i = 0 ; i < K ; i++) {
    m.mat[0][i] = cnt[i+1];
  }
  for(int i = 1 ; i < K ; i++) {
    m.mat[i][i-1] = 1;
  }
}

int work() {
  if(n <= K) {
    return dp[n];
  } else {
    m = m^(n - K);
    int ret = 0;

    for(int i = 0 ; i < K ; i++) {
      // cout << i << " " << m.mat[0][i] << " " << dp[K-i] << endl;
      ret = (ret + 1ll * m.mat[0][i] * dp[K - i]) % MOD;
    }

    return ret;
  }
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    read();
    prepare();
    int ret = work();

    if (ret == 0) {
      puts("IMPOSSIBLE");
    } else {
      printf("%d\n", ret);
    }
  }
  return 0;
}
