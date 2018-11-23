#include <bits/stdc++.h>
using namespace std;

string getString() {
  static char s[500005];
  scanf("%s", s);
  return (string)s;
}

// const int N = 10005;

char ans[500005];
int l, n;

int main() {
  memset(ans, -1, sizeof ans);
  int t; scanf("%d", &t);

  for (int tc = 1 ; tc <= t ; tc++) {
    scanf("%d %d", &l, &n);

    bool ok = true;

    for (int i = 0 ; i < n ; i++) {
      int a; scanf("%d", &a);
      a--;
      string s = getString();

      for (int j = 0 ; j < s.length() && s[j] != '*' ; j++) {
        int pos = a + j;
        if (ans[pos] != -1 && ans[pos] != s[j]) {
          ok = false;
          // printf("%c but become %c\n", ans[pos], s[j]);
          break;
        }
        ans[pos] = s[j];
      }

      for (int j = s.length()-1 ; j >= 0 && s[j] != '*' ; j--) {
        int pos = l - (s.length() - j);
        if (ans[pos] != -1 && ans[pos] != s[j]) {
          ok = false;
          // printf("%c but become %c\n", ans[pos], s[j]);
          break;
        }
        ans[pos] = s[j];
      }
    }

    for (int i = 0 ; i < l ; i++)
      if (ans[i] == -1)
        ok = false;

    if (!ok) puts("IMPOSSIBLE");
    else {
      ans[l] = '\0';
      printf("%s\n", ans);
    }

    for (int i = 0 ; i <= l ; i++) {
      ans[i] = -1;
    }
  }
  return 0;
}