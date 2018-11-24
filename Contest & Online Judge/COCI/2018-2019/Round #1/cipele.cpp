#include <bits/stdc++.h>
using namespace std;

vector<int> arr[2];
int n, m;

void read() {
  scanf("%d %d", &n, &m);
  for (int i = 0 ; i < n ; i++) {
    int x; scanf("%d", &x);
    arr[0].push_back(x);
  }
  for (int i = 0 ; i < m ; i++) {
    int x; scanf("%d", &x);
    arr[1].push_back(x);
  }
}

void prepare() {
  if (n > m) {
    swap(n, m);
    swap(arr[0], arr[1]);
  }

  sort(arr[0].begin(), arr[0].end());
  sort(arr[1].begin(), arr[1].end());
}

bool check(int diff) {
  int r = 0;
  for (int i = 0 ; i < n ; i++) {
    while (r < m && abs(arr[0][i] - arr[1][r]) > diff) r++;
    if (r == m) return false;
    r++;
  }
  return 1;
}

int work() {
  int lo = 0, hi = 1e9;
  while (lo < hi) {
    int mid = (lo + hi) / 2;

    if (check(mid)) hi = mid;
    else lo = mid+1;
  }
  return lo;
}

int main() {
  read();
  prepare();
  printf("%d\n", work());
  return 0;
}