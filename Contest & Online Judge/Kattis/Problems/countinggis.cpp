#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

int arr[N];
int n, l;

bool valid() {
  for(int i = 1 ; i < l ; i++) {
    if(arr[i] <= arr[i-1]) {
      return 0;
    }
  }

  return arr[l-1] == n;
}

void read() {
  scanf("%d %d", &n, &l);
  for(int i = 0 ; i < l ; i++) {
    scanf("%d", &arr[i]);
  }
}

int work() {
  if(!valid()) {
    return 0;
  }

  int ret = 1;
  int r = l-1;
  int slots = 0;

  for(int i = n ; i >= 1 ; i--) {
    while(r >= 0 && i < arr[r]) {
      r--;
      slots++;
    }

    if(r < 0 || i != arr[r]) {
      ret = 1ll * ret * slots % MOD;
      slots++;
    }
  }

  return ret;
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}