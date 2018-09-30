#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int BASE = 33;
const int MOD = 1e9 + 7;

string getString() {
  static char str[N];
  scanf("%s", str);
  return (string)str;
}

int pwr[N];
int val[N][26];
map<int,int> cnt;
unordered_set<int> asd;

void init() {
  pwr[0] = 1;
  for(int i = 1 ; i < N ; i++)
    pwr[i] = 1ll * pwr[i-1] * BASE % MOD;
  
  for(int i = 0 ; i < N ; i++)
    for(int j = 0 ; j < 26 ; j++)
      val[i][j] = 1ll * pwr[i] * (j+1) % MOD;
}

void make(string t) {
  int hsh = 0;
  for(int i = 0 ; i < t.length() ; i++) {
    hsh = (hsh + val[i][t[i] - 'a']) % MOD;
  }

  cnt[hsh]++;
  for(int i = 0 ; i < t.length() ; i++) {
    for(int j = 'a' ; j <= 'z' ; j++)
      if(j != t[i]) {
        int curHsh = hsh;
        curHsh = (curHsh - val[i][t[i] - 'a']) % MOD;
        curHsh = (curHsh + val[i][j - 'a']) % MOD;

        if (curHsh < 0) curHsh += MOD;
        cnt[curHsh]++;
      }
  }
}

int main() {
  init();
  string s = getString();
  string t = getString();
  string r = getString();

  make(t);
  make(r);

  for(auto it : cnt)
    if (it.second == 2)
      asd.insert(it.first);

  string ans = "";
  int hsh = 0;
  for (int i = 0; i < s.length(); i++) {
    hsh = (hsh + val[i][s[i] - 'a']) % MOD;
  }

  if (asd.count(hsh)) ans = s;

  for(int i = 0 ; i < s.length() ; i++)
    for (int j = 'a'; j <= 'z'; j++)
      if (j != s[i]) {
        int curHsh = hsh;
        curHsh = (curHsh - val[i][s[i] - 'a']) % MOD;
        curHsh = (curHsh + val[i][j - 'a']) % MOD;

        if (curHsh < 0) curHsh += MOD;

        if (asd.count(curHsh)) {
          if (ans != "") {
            cout << "Ambiguous\n";
            return 0;
          } else {
            ans = s;
            ans[i] = j;
          }
        }
      }
  
  if (ans == "") {
    cout << "Impossible\n";
  } else {
    cout << ans << endl;
  }
  return 0;
}