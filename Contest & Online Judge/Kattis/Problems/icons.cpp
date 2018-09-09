#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 5;

int n;
int arr[N];
long long suf_odd[N];
long long pref[N];

void read() {
  scanf("%d", &n);
  for(int i = 1 ; i <= 2 * n ; i++) {
    scanf("%d", &arr[i]);
  }
}

void prepare() {
  for(int i = 2*n - 1 ; i >= 0 ; i -= 2) {
    suf_odd[i] = suf_odd[i + 2] + arr[i];
  }
  for(int i = 1 ; i <= 2 * n ; i++) {
    pref[i] = pref[i-1] + arr[i];
  }
}

long long work() {
  long long ret = 4e18;

  for(int i = n+1 ; i >= 2 ; i--) {
    long long height = arr[1] + arr[i];
    long long width = pref[i-1];
    
    int used = i - 2;
    int skip = i + used + 1;

    if((2 * n + 1 - skip) % 2 == 0) {
      width += suf_odd[skip];
      ret = min(ret, height * width);
    }
  }

  return ret;
}

int main() {
  read();
  prepare();
  printf("%lld\n", work());
  return 0;
}