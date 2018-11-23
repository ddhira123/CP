#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  double ret = 1;
  double cur = 1;

  n = min(n, 15);
  for (int i = 1 ; i <= n ; i++) {
    cur /= i;
    ret += cur;
  }

  printf("%.15lf\n", ret);
  return 0;
}