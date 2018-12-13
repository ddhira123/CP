#include <bits/stdc++.h>
using namespace std;

const int MX = 2e6 + 5;

int cnt[MX];
int flag[MX];

int main() {
  for (int i = 2 ; i < MX ; i++) {
    if (!flag[i]) {
      for (int j = i ; j < MX ; j += i)
        flag[j] = 1;
    } else {
      for (int j = i ; j < MX ; j += i)
        cnt[j]++;
    }
  }

  int q; scanf("%d", &q);
  for (int i = 0 ; i < q ; i++) {
    int x; scanf("%d", &x);

    printf("%d\n", cnt[x] + 1);
  }
  return 0;
}