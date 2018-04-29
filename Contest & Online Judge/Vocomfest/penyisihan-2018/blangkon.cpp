#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

char s[N];

void read() {
  scanf("%s", s);
}

string work() {
  string ret = "";
  int len = strlen(s);

  for(int i = 0 ; i < len ; ) {
    int j = i;
    while(s[j] != '/') {
      j++;
    }

    if(s[i] == '#') {
      ret += " ";
    } else {
      int ch = -1;
      for(int k = i ; k < j ; k++) {
        if(s[k] == '-') {
          ch += (1 << (j - k - 1));
        }
      }

      ret += (char)(ch + 'A');
    }
    
    i = j+1;
  }

  return ret;
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    read();
    string ret = work();

    printf("Case #%d: %s\n", tc, ret.c_str());
  }
  return 0;
}