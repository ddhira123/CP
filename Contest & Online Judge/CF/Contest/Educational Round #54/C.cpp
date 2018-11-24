#include <bits/stdc++.h>
using namespace std;

void work(int n) {
  if (1 <= n && n <= 3) {
    puts("N");
    return;
  }
  if (n == 0) {
    printf("Y 0 0\n");
    return;
  }

  int d = n * n - 4 * n;
  double b1 = (n + sqrt(d)) / 2;
  double a1 = b1 / (b1 - 1);

  printf("Y %.9lf %.9lf\n", a1, b1);
}

int main() {
  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    int n; cin >> n;
    work(n);
  }
  return 0;
}