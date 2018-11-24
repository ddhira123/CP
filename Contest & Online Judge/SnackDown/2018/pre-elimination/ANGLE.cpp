#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

pair<int, int> arr[N];
int n, p, q;

pair<long long, long long> optimalCos;
int x, y, z;

void read() {
  scanf("%d %d %d", &n, &p, &q);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &arr[i].first);
    arr[i].second = i;
  }
}

pair<long long, long long> getCosine(long long a, long long b, long long c) {
  long long atas = c * c - a * a - b * b;
  long long bawah = -2 * a * b;

  atas = -atas;
  bawah = -bawah;

  return {atas, bawah};
}

bool isLessFrac(pair<long long, long long> a, pair<long long, long long> b) {
  return a.first * b.second <= a.second * b.first;
}

void check(int a) {
  for (int b = 1 ; b <= n ; b++) {
    if (a == b) continue;

    int xx = arr[a].first;
    int yy = arr[b].first;

    int low = lower_bound(arr + 1, arr + n + 1, make_pair(abs(xx-yy)+1, -1)) - arr;
    int high = lower_bound(arr + 1, arr + n + 1, make_pair(xx+yy+1, -1)) - arr;

    // printf("a %d b %d low %d high %d\n", a, b, low, high);
    if (low == high) continue;

    int lo = low, hi = high-1;
    while (lo < hi) {
      int mid = (lo + hi + 1) / 2;
      pair<long long, long long> cur = getCosine(xx, yy, arr[mid].first);

      if (isLessFrac({p, q}, cur)) {
        lo = mid;
      } else {
        hi = mid-1;
      }
    }

    for (int j = max(low, lo-2) ; j < min(high, lo+2) ; j++) {
      pair<long long, long long> cur = getCosine(xx, yy, arr[j].first);
      // printf("%d %d %d cur %lld %lld\n", xx, yy, arr[j].first, cur.first, cur.second);

      if (isLessFrac({p, q}, cur) && j != a && j != b) {
        if (optimalCos.first == -1 || isLessFrac(cur, optimalCos)) {
          optimalCos = cur;

          x = arr[j].second;
          y = arr[a].second;
          z = arr[b].second;
        }
      }
    }
  }
}

void work() {
  optimalCos = {-1, -1};
  x = -1;
  sort(arr + 1, arr + n + 1);

  for (int i = 1 ; i <= n ; i++)
    check(i);
  
  if (x == -1) {
    puts("-1");
  } else {
    printf("%d %d %d\n", x, y, z);
  }
}

int main() {
  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    read();
    work();
  }
  return 0;
}