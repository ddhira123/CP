#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;
const int Q = 1e5 + 5;
const int INF = 1e9 + 1;

struct Event {
  int x;
  int tipe;
  int val;

  bool operator <(Event other) const {
    return x < other.x;
  }
};

int ql[Q], qr[Q];
long long k[Q];

int x[N], y[N], z[N];
int l[N], r[N];
int m1, m2, m3;
int a1, a2, a3;
int b1, b2, b3;
int c1, c2, c3;

Event events[2 * N];

int n, q;

void init() {
  scanf("%d %d", &n, &q);
  scanf("%d %d %d %d %d %d", &x[1], &x[2], &a1, &b1, &c1, &m1);
  scanf("%d %d %d %d %d %d", &y[1], &y[2], &a2, &b2, &c2, &m2);
  scanf("%d %d %d %d %d %d", &z[1], &z[2], &a3, &b3, &c3, &m3);

  for (int i = 3 ; i <= n ; i++) {
    x[i] = (1ll * a1 * x[i - 1] + 1ll * b1 * x[i - 2] + c1) % m1;
    y[i] = (1ll * a2 * y[i - 1] + 1ll * b2 * y[i - 2] + c2) % m2;
  }

  for (int i = 3 ; i <= q ; i++) {
    z[i] = (1ll * a3 * z[i - 1] + 1ll * b3 * z[i - 2] + c3) % m3;
  }

  for (int i = 1 ; i <= n ; i++) {
    l[i] = min(x[i], y[i]) + 1;
    r[i] = max(x[i], y[i]) + 1;
  }

  for (int i = 1 ; i <= q ; i++) {
    k[i] = z[i] + 1;
  }

  // // // debug
  // printf("x = [");
  // for (int i = 1 ; i <= n ; i++) {
  //   printf("%d, ", x[i]);
  // }
  // puts("]");

  // printf("y = [");
  // for (int i = 1; i <= n; i++) {
  //   printf("%d, ", y[i]);
  // }
  // puts("]");

  // printf("z = [");
  // for (int i = 1; i <= q; i++) {
  //   printf("%d, ", z[i]);
  // }
  // puts("]");

  // for (int i = 1 ; i <= n ; i++) {
  //   printf("(%d,%d)\n", l[i], r[i]);
  // }
  // for (int i = 1; i <= q; i++) {
  //   printf("(%d)\n", k[i]);
  // }
}

void prepare() {
  for (int i = 1 ; i <= n ; i++) {
    events[2 * i - 1] = (Event){l[i], 1, -(l[i]-1)};
    events[2 * i] = (Event){r[i]+1, -1, l[i]-1 + (r[i]-l[i]+1)};
  }
  sort(events + 1, events + 2*n + 1);

  long long sums = 0;
  for (int i = 1 ; i <= n ; i++) {
    sums += (r[i] - l[i] + 1);
  }

  for (int i = 1 ; i <= q ; i++) {
    if (k[i] > sums) {
      ql[i] = -1;
      qr[i] = -1;
      continue;
    }

    k[i] = sums - k[i] + 1;
    ql[i] = 0;
    qr[i] = INF;
  }
}

unsigned long long work() {
  while(1) {
    // x, index
    vector<pair<int, int>> v;
    for (int i = 1 ; i <= q ; i++) {
      if (ql[i] == qr[i]) continue;
      v.push_back({(ql[i] + qr[i]) / 2, i});
    }

    if (v.empty()) break;

    sort(v.begin(), v.end());

    int it = 1;
    long long occ = 0;
    long long sums = 0;

    for (pair<int, int> que : v) {
      int idx = que.second;
      int x = que.first;

      while (it <= 2 * n && events[it].x <= x) {
        occ += events[it].tipe;
        sums += events[it].val;

        it++;
      }

      long long under = occ * x + sums;
      // printf("x %d idx %d under %lld k %d\n", x, idx, under, k[idx]);
      if (under >= k[idx]) {
        qr[idx] = x;
      } else {
        ql[idx] = x+1;
      }
    }
  }

  unsigned long long ret = 0;
  for (int i = 1 ; i <= q ; i++) {
    if (ql[i] != -1) {
      unsigned long long cur = i;
      cur *= ql[i];
      ret += cur;
    }
  }
  
  return ret;
}

int main() {
  int t;  cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    cerr << tc << endl;
    init();
    prepare();
    printf("Case #%d: %llu\n", tc, work());
  }
  return 0;
}