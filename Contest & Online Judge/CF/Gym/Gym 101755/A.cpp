#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, g;
  cin >> n >> g;

  if (n % g == 0 && n != g) {
    cout << g << " " << n-g << endl;
  } else {
    cout << -1 << endl;
  }
  return 0;
}