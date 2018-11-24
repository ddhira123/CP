#include <bits/stdc++.h>
using namespace std;

int t, n, m, i;
vector<int> a, b;
bool yes;

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    a.clear(); b.clear();
    for (i = 0; i < n; i++) {
      int x; scanf("%d", &x);
      if (x)
        a.push_back(x);
    }
    for (i = 0; i < m; i++) {
      int x; scanf("%d", &x);
      if (x)
        b.push_back(x);
    }

    n = a.size(); m = b.size();

    yes = true;
    if (n == m) {
      yes = false;
      sort(a.begin(), a.end());
      sort(b.begin(), b.end());
      for (i = 0; i < n; i++)
        if (a[i] != b[i]) yes = true;
    }
    if (yes)
      printf("Alice\n");
    else
      printf("Bob\n");
  }
}
