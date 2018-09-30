#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 5;

int cnt[MX];
int n, m;

void read() {
  scanf("%d %d", &n, &m);

  for(int i = 0 ; i < n ; i++) {
    int x; scanf("%d", &x);
    cnt[x]++;
  }
}

int work() {
  int ret = 1;
  for(int i = 2 ; i < MX ; i++) {
    int tot = 0;
    for(int j = i ; j < MX && tot < m ; j += i) {
      tot += cnt[j];
    }
    if(tot >= m) ret = i;
  }
  return ret;
}

void reset() {
  memset(cnt, 0, sizeof cnt);
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    read();
    printf("%d\n", work());
    reset();
  }
  return 0;
}