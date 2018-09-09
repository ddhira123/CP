#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  int ret = -1;

  for(int len = 1 ; ret == -1 ; len++) {
    int middle = (len - 1) / 2;
    int nums = 1 << (middle);

    if(nums >= n) {
      ret = 1;
      ret |= (1 << (len-1));

      for(int i = 1 ; i <= middle ; i++) {
        int sisa = 1 << (middle - i);
        
        if(n > sisa) {
          n -= sisa;
          ret |= (1 << i);
          ret |= (1 << (len-1-i));
        }
      }
    } else {
      n -= nums;
    }
  }

  cout << ret << endl;
  return 0;
}