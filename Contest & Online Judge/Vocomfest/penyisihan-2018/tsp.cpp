#include <bits/stdc++.h>
using namespace std;

int brute(int n) {
  int ret = 0;

  for(int i = -n ; i <= n ; i++)
    for(int j = -n ; j <= n ; j++) {
      if(i + j >= -n && i + j <= n) {
        ret = (ret + 1) % 10;
      }
    }
  
  return ret;
}

int main() {
  // for(int i = 1 ; i <= 100 ; i++) {
  //   printf("%d -> %d\n", i, brute(i));
  // }
  int t; cin >> t;
  int result[] = {1, 7, 9, 7, 1};

  for(int tc = 1 ; tc <= t;  tc++) {
    long long n; cin >> n;
    int ret = result[n % 5];

    printf("Case #%d: %d\n", tc, ret);
  }
  return 0;
}