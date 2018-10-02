#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  int ret = 0;

  for(int i = 0 ; i < n ; i++) {
    string x; cin >> x;
    int len = x.length();

    int num = stoi(x.substr(0, len-1));
    int pwr = stoi(x.substr(len-1, 1));

    int val = 1;
    for(int j = 0 ; j < pwr ; j++)
      val *= num;
    
    ret += val;
  }
  
  cout << ret << "\n";
  return 0;
}