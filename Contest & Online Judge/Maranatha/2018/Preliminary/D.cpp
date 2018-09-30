#include <bits/stdc++.h>
using namespace std;

int main() {
  int t = 1;
  for(int tc = 1 ; tc <= t ; tc++) {
    string s; cin >> s;
    int comma = s.find(",");

    int a = stoi(s.substr(0, comma));
    int b = stoi(s.substr(comma+1));

    int ret = 1;
    for(int i = 1 ; i*i <= a ; i++) {
      if(a % i == 0) {
        if(b % i == 0) ret = max(ret, i);
        if(b % (a / i) == 0) ret = max(ret, a / i);
      }
    }

    printf("%d\n", ret);
  }
  return 0;
}