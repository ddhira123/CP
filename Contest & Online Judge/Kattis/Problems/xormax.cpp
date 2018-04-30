#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<long long> basis;
long long arr[N];
int n;

void read() {
  scanf("%d", &n);
  for(int i = 0 ; i < n ; i++) {
    scanf("%lld", &arr[i]);
  }
}

long long work() {
  for(int bit = 62 ; bit >= 0 ; bit--) {
    int idx = -1;

    for(int i = 0 ; i < n ; i++) {
      if(idx == -1 || arr[i] > arr[idx]) {
        idx = i;
      }
    }

    if(idx != -1) {
      swap(arr[idx], arr[n-1]);

      if(arr[n-1] & (1ll << bit)) {
        basis.push_back(arr[n-1]);
        n--;

        for(int i = 0 ; i < n ; i++) {
          if(arr[i] & (1ll << bit)) {
            arr[i] ^= basis.back();
          }
        }
      }
    }
  }

  long long ret = 0;
  for(long long x : basis) {
    if((ret ^ x) > ret) {
      ret ^= x;
    }
  }

  return ret;
}

int main() {
  read();
  printf("%lld\n", work());
  return 0;
}