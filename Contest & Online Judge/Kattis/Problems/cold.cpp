#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  vector<int> v(n);

  for(int &x : v) cin >> x;
  cout << count_if(v.begin(), v.end(), [](int x) { return x < 0;}) << endl;
  return 0;
}