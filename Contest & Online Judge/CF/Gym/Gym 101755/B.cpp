#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int x[N], y[N];
int n;

void read() {
  scanf("%d", &n);
  for(int i = 0 ; i < n ; i++)
    scanf("%d %d", &x[i], &y[i]);
}

long long work() {
  long long ret = 8e18;

  for(int i = 0 ; i < n ; i++) {
    int j = (i + 1) % n;
    int k = (i + 2) % n;

    long long a = 1ll * x[i] * y[j];
    a += 1ll * x[j] * y[k];
    a += 1ll * x[k] * y[i];

    long long b = 1ll * x[i] * y[k];
    b += 1ll * x[j] * y[i];
    b += 1ll * x[k] * y[j];

    long long area = abs(a - b);
    if (area != 0) ret = min(ret, area);
  }

  return ret;
}

int main() {
  read();
  printf("%lld\n", work());
  return 0;
}