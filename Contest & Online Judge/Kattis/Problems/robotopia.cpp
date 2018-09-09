#include <bits/stdc++.h>
using namespace std;

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    int a1, l1, a2, l2, at, lt;
    cin >> a1 >> l1 >> a2 >> l2 >> at >> lt;

    vector<pair<int, int>> ans;
    for(int i = 1 ; a1 * i <= at && l1 * i <= lt ; i++) {
      int a_left = at - a1 * i;
      int l_left = lt - l1 * i;

      if(a_left >= 1 && l_left >= 1 && a_left % a2 == 0 && l_left % l2 == 0) {
        int a_use = a_left / a2;
        int l_use = l_left / l2;

        if(a_use == l_use) {
          ans.push_back({i, a_use});
        }
      }
    }

    if(ans.size() == 1) {
      printf("%d %d\n", ans[0].first, ans[0].second);
    } else {
      puts("?");
    }
  }
  return 0;
}