#include <bits/stdc++.h>
using namespace std;

const int N = 15005;
const int M = 30005;
const int MOD = 1e9 + 7;

int pset[N];
pair<int, pair<int, int>> arr[M];
int ways[N];
int n, m;

void add(int x) {
  for (int i = n ; i >= x ; i--) {
    ways[i] = (ways[i] + ways[i-x]) % MOD;
  }
}

void remove(int x) {
  for (int i = x ; i <= n ; i++) {
    ways[i] = (ways[i] - ways[i-x] + MOD) % MOD;
  }
}

int finds(int x) {
  return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

void join(int x, int y) {
  x = finds(x);
  y = finds(y);
  if (x != y) {
    pset[x] += pset[y];
    pset[y] = x;
  }
}

void read() {
  scanf("%d %d", &n, &m);
  for (int i = 0 ; i < m ; i++) {
    scanf("%d %d %d", &arr[i].second.first, &arr[i].second.second, &arr[i].first);
  }
}

double work() {
  ways[0] = 1;
  for (int i = 1 ; i <= n ; i++)
    add(1);

  memset(pset, -1, sizeof pset);
  sort(arr, arr + m);
  reverse(arr, arr + m);

  double ret = 1e9;
  for (int i = 0 ; i < m ; i++) {
    int x = arr[i].second.first;
    int y = arr[i].second.second;

    x = finds(x);
    y = finds(y);

    if (x != y) {
      int szx = -pset[x];
      int szy = -pset[y];
      remove(szx);
      remove(szy);

      for (int j = 0 ; j <= n ; j++)
        if (ways[j] != 0) {
          int a = min(szx + j, szy + n - j - szx - szy);
          int b = min(szy + j, szx + n - j - szx - szy);
          int c = max(a, b);

          ret = min(ret, 1.0 * arr[i].first / c);
        }
      
      join(x, y);
      add(szx + szy);
    }
  }

  return ret;
}

int main() {
  read();
  printf("%.9lf\n", work());
  return 0;
}