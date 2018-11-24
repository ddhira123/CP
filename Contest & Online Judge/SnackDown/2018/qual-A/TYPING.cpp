#include <bits/stdc++.h>
using namespace std;

int hand(char ch) {
  return (ch == 'd' || ch == 'f') ? 1 : 2;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);

  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    set<string> seen;
    int n; cin >> n;

    int ret = 0;
    for (int i = 0 ; i < n ; i++) {
      string s; cin >> s;
      int cur = 0;
      int tot = 0;

      for (char ch : s) {
        if (hand(ch) == cur) tot += 4;
        else tot += 2;
        cur = hand(ch);
      }

      if (seen.count(s)) tot /= 2;
      else seen.insert(s);

      ret += tot;
    }

    cout << ret << endl;
  }
  return 0;
}