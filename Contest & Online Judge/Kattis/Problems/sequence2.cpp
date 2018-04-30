#include <bits/stdc++.h>
using namespace std;

int n;
long long ans;

int main() {
  scanf("%d", &n);
  int lst = -1;

  for(int i = 1 ; i <= n ; i++) {
    int x; scanf("%d", &x);
    if(i > 1) {
      ans += max(lst, x);
    }
    lst = x;
  }

  printf("%lld\n", ans);
  return 0;
}