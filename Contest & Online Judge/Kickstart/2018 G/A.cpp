#include <bits/stdc++.h>
using namespace std;

const int N = 7005;
const int MX = 2e5 + 5;

int arr[N];
int cnt[MX];
int n;

void read() {
  scanf("%d", &n);
  for (int i = 0 ; i < n ; i++) {
    scanf("%d", &arr[i]);
  }
}

int bf() {
  int ret = 0;
  for (int i = 0 ; i < n ; i++)
    for (int j = i+1 ; j < n ; j++)
      for (int k = j+1 ; k < n ; k++) {
        int x = arr[i];
        int y = arr[j];
        int z = arr[k];

        if (1ll * x * y == z || 1ll * x * z == y || 1ll * y * z == x) {
          ret++;
        }
      }
  return ret;
}

long long c2(long long x) {
  return x * (x - 1) / 2;
}

long long c3(long long x) {
  return x * (x-1) * (x-2) / 6;
}

// real shit
long long work() {
  memset(cnt, 0, sizeof cnt);

  for (int i = 0 ; i < n ; i++) {
    cnt[arr[i]]++;
  }

  long long ret = 0;

  // calculate distinct
  for (int i = 2 ; i < MX ; i++) {
    for (int j = i+1 ; 1ll * i * j < MX ; j++) {
      ret += 1ll * cnt[i] * cnt[j] * cnt[i * j];
      // printf("i %d j %d -> %d %d %d\n", i, j, cnt[i], cnt[j], cnt[i*j]);
    }
  }

  // cout << ret << endl;

  // calculate sqr
  for (int i = 2 ; i * i < MX ; i++) {
    ret += 1ll * c2(cnt[i]) * cnt[i*i];
  }

  // calculate using exactly one 1
  for (int i = 2 ; i < MX ; i++) {
    ret += 1ll * cnt[1] * c2(cnt[i]);
  }

  // calculate using three 1
  ret += c3(cnt[1]);

  // using exactly two zero
  ret += 1ll * c2(cnt[0]) * (n - cnt[0]);

  // using three 0
  ret += c3(cnt[0]);

  return ret;
}

int main() {
  int t; cin >> t;

  for (int tc = 1 ; tc <= t ; tc++) {
    read();
    // printf("Case #%d: %d\n", tc, bf());
    printf("Case #%d: %lld\n", tc, work());
  }
  return 0;
}