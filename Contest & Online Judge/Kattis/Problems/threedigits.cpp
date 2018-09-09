#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9;

long long get_five(int n) {
  return n == 0 ? 0 : n / 5 + get_five(n / 5); 
}

int main() {
  int n; cin >> n;
  long long fives = get_five(n);
  long long twos = fives;

  long long ret = 1;

  for(int i = 1 ; i <= n ; i++) {
    int x = i;
    while(fives > 0 && x % 5 == 0) {
      fives--;
      x /= 5;
    }
    while(twos > 0 && x % 2 == 0) {
      twos--;
      x /= 2;
    }

    ret = ret * x % 1000;
  }

  if (n <= 7) {
    printf("%lld\n", ret % 1000);
  } else {
    printf("%03lld\n", ret % 1000);
  }
  return 0;
}