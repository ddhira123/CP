#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int l[N];
int h[N];
long long psum[N];
long long water[N];
int n, q;

void read() {
  scanf("%d", &n);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &l[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &h[i]);
  }
}

void prepare() {
  h[0] = 1e9 + 5;
  l[0] = -1;
  for (int i = 1 ; i <= n ; i++) {
    psum[i] = psum[i-1] + h[i];
  }

  vector<int> stek;
  stek.push_back(0);

  for (int i = 1 ; i <= n ; i++) {
    while (!stek.empty() && h[stek.back()] <= h[i]) {
      stek.pop_back();
    }

    int bef = stek.back();
    water[i] = water[bef];
    water[i] += 1ll * (l[i] - l[bef] - 1) * h[i];
    water[i] -= (psum[i-1] - psum[bef]);

    // printf("i %d water %lld\n", i, water[i]);
    stek.push_back(i);
  }
}

void work() {
  scanf("%d", &q);
  for (int i = 0 ; i < q ; i++) {
    long long x; scanf("%lld", &x);
    int pos = upper_bound(water, water + n + 1, x-1) - water;

    printf("%d\n", pos-1);
  }
}

int main() {
  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    read();
    prepare();
    work();
  }
  return 0;
}