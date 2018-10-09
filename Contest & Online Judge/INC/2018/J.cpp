#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int arr[N];
int n, m;

int main() {
  scanf("%d %d", &n, &m);
  for(int i = 0 ; i < n ; i++) {
    scanf("%d", &arr[i]);
  }
  sort(arr, arr + n);

  if (n <= m) {
    long long x = accumulate(arr, arr + n, 0ll);
    printf("%lld %lld\n", x, x);
    return 0;
  }

  long long mins = 0;
  for (int i = 0 ; i < m ; i++)
    mins += arr[i];
  
  int part = n / m;
  int sisa = n % m;

  long long mx1 = 0, mx2 = 0;
  {
    int cur = 0;
    for (int i = 0 ; i < sisa ; i++) {
      mx1 += arr[cur];
      cur += part+1;
    }
    for (int i = 0 ; i < m-sisa ; i++) {
      mx1 += arr[cur];
      cur += part;
    }
  }
  {
    int cur = 0;
    for (int i = 0; i < m-sisa; i++) {
      mx2 += arr[cur];
      cur += part;
    }
    for (int i = 0; i < sisa; i++) {
      mx2 += arr[cur];
      cur += part+1;
    }
  }

  printf("%lld %lld\n", mins, max(mx1, mx2));
  return 0;
}