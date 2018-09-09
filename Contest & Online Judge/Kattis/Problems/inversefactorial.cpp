#include <bits/stdc++.h>
using namespace std;

int solve(string s) {
  if(s == "1") return 1;
  if(s == "2") return 2;
  if(s == "6") return 3;
  if(s == "24") return 4;
  if(s == "120") return 5;
  if(s == "720") return 6;
  if(s == "5040") return 7;
  if(s == "40320") return 8;
  if(s == "362880") return 9;
  if(s == "3628800") return 10;

  double logg = 0;
  for(int i = 2 ; ; i++) {
    logg += log10(i);
    if((int)ceil(logg) == s.length()) {
      return i;
    }
  }

  return -1;
}

int main() {
  string s; cin >> s;
  cout << solve(s) << endl;
  return 0;
}