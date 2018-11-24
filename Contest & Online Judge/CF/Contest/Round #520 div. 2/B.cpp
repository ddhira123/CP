#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  if (n == 1) {
    cout << "1 0" << endl;
    return 0;
  }

  int mx = 0;
  int mn = 1e9;
  int mul = 1;

  for (int i = 2 ; n > 1 ; i++)
    if (n % i == 0) {
      mul *= i;
      int cnt = 0;
      while (n % i == 0) {
        cnt++;
        n /= i;
      }
      mx = max(mx, cnt);
      mn = min(mn, cnt);
    }
  
  int ans = 0;
  int it = 1;
  while (it < mx) {
    it *= 2;
    ans++;
  }

  ans += (mn != it);

  cout << mul << " " << ans << endl;
  return 0;
}