#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

string dpRev[N], dpFor[N];
string s;
int n;

void read() {
  cin >> s;
  n = s.length();
}

void work() {
  string cur = "";
  
  for (int i = 0 ; i < n-1 ; i++) {
    cur += s[i];

    if (cur[i] == s[i+1]) {
      cout << 0;
    } else {
      reverse(cur.begin(), cur.end());
      cout << 1;
    }

    cout << " ";
  }

  cur += s[n-1];
  if (s[n-1] == 'a') {
    reverse(cur.begin(), cur.end());
    cout << 1;
  } else {
    cout << 0;
  }

  cout << endl;

  // cout << cur << endl;
}

int main() {
  read();
  work();
  return 0;
}