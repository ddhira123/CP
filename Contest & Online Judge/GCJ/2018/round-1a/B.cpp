#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const long long INF = 4e18;

int r, b, c;
int m[N], s[N], p[N];

int calc_max(int idx, long long lmt) {
  if(lmt < p[idx]) return 0;

  return min(1ll * m[idx], (lmt - p[idx]) / s[idx]);
}

bool check(long long lmt) {
  vector<int> v;

  for(int i = 0 ; i < c ; i++) {
    v.push_back(calc_max(i, lmt));
  }

  sort(v.begin(), v.end());
  reverse(v.begin(), v.end());
  int sisa = b;

  for(int i = 0 ; i < r ; i++) {
    sisa -= v[i];
    if(sisa <= 0) {
      return true;
    }
  }

  return false;
}

void read() {
  scanf("%d %d %d", &r, &b, &c);
  for(int i = 0 ; i < c ; i++) {
    scanf("%d %d %d", &m[i], &s[i], &p[i]);
  }
}

long long work() {
  long long lo = 0, hi = INF;

  while(lo < hi) {
    long long mid = (lo + hi) / 2;

    if(check(mid)) {
      hi = mid;
    } else {
      lo = mid+1;
    }
  }

  return lo;
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    read();
    printf("Case #%d: %lld\n", tc, work());
  }
  return 0;
}