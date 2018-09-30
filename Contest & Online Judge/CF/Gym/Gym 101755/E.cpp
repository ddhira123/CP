#include <bits/stdc++.h>
using namespace std;

int main() {
  string s, t;
  cin >> s >> t;

  int i = 0;
  while (i < s.length() && s[i] == t[i]) i++;
  int j = s.length()-1;
  while (j >= 0 && s[j] == t[j]) j--;

  bool ok = i == s.length();
  if (!ok) {
    string subS = s.substr(i, j-i+1);
    string subT = t.substr(i, j - i + 1);
    // cout << subS << endl;
    reverse(subS.begin(), subS.end());

    ok = subS == subT;
  }

  if (ok) cout << "YES\n";
  else cout << "NO\n";
  return 0;
}