#include <bits/stdc++.h>
using namespace std;

int n, m, x, y;

long long C2(long long z) {
  return z * (z - 1) / 2;
}

long long calcRow() {
  long long ret = 0;

  for (int i = 1 ; i <= m ; i++) {
    if (y == i) {
      for (int j = 1 ; j < x ; j++) {
        ret += (x - j - 1);
      }
      for (int j = x + 1 ; j < n ; j++) {
        ret += (n - j);
      }
    } else {
      ret += C2(n); 
    }

    // cout << i << " " << ret << endl;
  }

  // printf("row %lld\n", ret);
  return ret;
}

long long calcColumn() {
  long long ret = 0;

  for (int i = 1; i <= n ; i++) {
    if (x == i) {
      for (int j = 1; j < y; j++) {
        ret += (y - j - 1);
      }
      for (int j = y + 1; j < m; j++) {
        ret += (m - j);
      }
    } else {
      ret += C2(m);
    }
  }

  // printf("column %lld\n", ret);
  return ret;
}

long long calcDiagonal(int a, int b) {
  long long ret = 0;

  for (int i = 1 ; i <= n ; i++)
    for (int j = 1 ; j <= m ; j++) {
      if (a == i && b == j) continue;

      if (a >= i && b >= j && a-i == b-j) {
        int mins = a-i;
        ret += (mins-1);
      } else {
        int mins = min(n-i, m-j);
        ret += mins;
      }
    }
  
  // printf("dia %lld\n", ret);
  return ret;
}

int main() {
  int t; cin >> t;

  for (int tc = 1 ; tc <= t ; tc++) {
    long long ret = 0;

    cin >> n >> m >> x >> y;

    ret = n * m - 1;
    ret = C2(ret);

    // cout << ret << endl;

    ret -= calcRow();
    ret -= calcColumn();
    ret -= calcDiagonal(x, y);
    ret -= calcDiagonal(x, m-y+1);

    cout << ret*2 << endl;
  }
  return 0;
}