#include <bits/stdc++.h>
using namespace std;

long long getPrime(long long x) {
  for (int i = 2 ; 1ll * i * i <= x ; i++) {
    if (x % i == 0) return i;
  }
  return x;
}

int main() {
  long long n;
  cin >> n;

  long long ans = 1;
  n -= getPrime(n);

  if (n != 0) ans += n / 2;

  cout << ans << endl;
  return 0;
}