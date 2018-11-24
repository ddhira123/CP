#include <bits/stdc++.h>
using namespace std;

const int N = 5e6 + 5;
string s;

int psum[N];
int n;

void read() {
  cin >> n >> s;
}

void make() {
  for (int i = 1 ; i <= n ; i++) {
    psum[i] = s[i-1] - '0' + psum[i-1];
  }
}

int get(int l) {
  int lo = l, hi = n;
  while (lo < hi) {
    int mid = (lo + hi + 1) / 2;
    int len = mid - l + 1;

    if (l + 2 * (len - 1) <= n) {
      lo = mid; 
    } else {
      hi = mid-1;
    }
  }

  // printf("l %d lo %d\n", l, lo);
  return lo;
}

int solve() {
  int half = (n + 1) / 2;
  int ret = 0;

  for (int i = 1 ; i+half-1 <= n ; i++) {
    int kanan = get(i);
    kanan = i+half-1;
    // printf("i %d kanan %d asd %d\n", i, kanan, psum[kanan] - psum[i-1]);
    ret = max(ret, psum[kanan] - psum[i-1]);
  }
  return ret;
}

int work() {
  int ret = 0;
  make();

  ret = max(ret, solve());

  reverse(s.begin(), s.end());
  make();
  ret = max(ret, solve());

  return ret;
}

int main() {
  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    read();
    
    int ret = work();
    printf("Case #%d: %d\n", tc, ret);
  }
  return 0;
}