#include <bits/stdc++.h>
using namespace std;

int main() {
  string s; cin >> s;
  long long ret = 0;

  string tmp = "";
  int cur = 0;
  for(int i = 0 ; i < s.length() ; i++) {
    if(s[i] == '0') {
      ret += abs(cur - i);
      cur++;
    } else {
      tmp += s[i];
    }
  }

  s = tmp;
  tmp = "";
  cur = 0;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '1') {
      ret += abs(cur - i);
      cur++;
    } else {
      tmp += s[i];
    }
  }

  printf("%lld\n", ret);
  return 0;
}