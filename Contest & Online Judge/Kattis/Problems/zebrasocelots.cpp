#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  long long ret = 0;

  for(int i = n-1 ; i >= 0 ; i--) {
    string x; cin >> x;
    if (x == "O") ret |= (1ll << i);
  }

  cout << ret << endl;
  return 0;
}