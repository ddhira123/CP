#include <bits/stdc++.h>
using namespace std;

map<string, int> ms;

int check(string str) {
  if(ms.count(str)) {
    return ms[str];
  }

  set<int> st;
  for(int i = 0 ; i < str.length() ; i++) {
    if(str[i] == 'B') {
      string tmp = str;
      tmp[i] = 'A';
      int ret = check(tmp);
      // cout << str << " " << tmp << " " << ret << endl;

      st.insert(ret);
    }
    if(i+1 < str.length() && str[i] == 'A' && str[i+1] == 'B') {
      string tmp = str;
      swap(tmp[i], tmp[i+1]);
      int ret = check(tmp);

      // cout << str << " " << tmp << " " << ret << endl;

      st.insert(ret);
    }
  }

  for(int i = 0 ; ; i++) {
    if(!st.count(i)) {
      return ms[str] = i;
    }
  }
}

void rec(int len, string str) {
  if(len == 0) {
    cout << str << ": " << check(str) << endl;
  } else {
    for(char ch = 'A' ; ch <= 'B' ; ch++) {
      string tmp = str;
      tmp += ch;
      rec(len-1, tmp);
    }
  }
}

int main() {
  // for(int i = 1 ; i <= 5 ; i++) {
  //   rec(i, "");
  // }
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    string str; cin >> str;
    reverse(str.begin(), str.end());

    int mods = 0;
    int mul = 1;
    for(char ch : str) {
      if(ch == 'B') {
        mods = (mods + mul) % 3;
      }

      mul = mul * 2 % 3;
    }

    // cout << mul << " " << mods << " " << str << endl;

    string ret = "Semar";
    if(mods > 0) {
      ret = "Gareng";
    }

    printf("Case #%d: %s\n", tc, ret.c_str());
  }
  return 0;
}