#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

string getString() {
  static char str[N];
  scanf("%s", str);
  return (string)str;
}

int nxt[N][26];
string s;
int n;

int main() {
  s = getString();
  n = s.length();

  for(int i = 0 ; i < 26 ; i++)
    nxt[n][i] = n;

  for(int i = n-1 ; i >= 0 ; i--) {
    for(int j = 0 ; j < 26 ; j++)
      nxt[i][j] = nxt[i+1][j];
    nxt[i][s[i] - 'a'] = i;
  }

  string p;
  vector<int> pos;
  pos.push_back(-1);

  int q; scanf("%d", &q);
  for(int i = 0 ; i < q ; i++) {
    string opt = getString();

    if (opt == "push") {
      string tmp = getString();
      char ch = tmp[0];

      // actually append
      if (pos.size() == p.length()+1) {
        if (pos.back() != n-1 && nxt[pos.back()+1][ch-'a'] < n) {
          pos.push_back(nxt[pos.back()+1][ch-'a']);
        }
      }

      p += ch;
    } else {
      if (pos.size() == p.length() + 1) {
        pos.pop_back();
      }

      p.erase(p.begin() + p.length() - 1);
    }

    printf("%s\n", pos.size() == p.length() + 1 ? "YES" : "NO");
  }
  return 0;
}