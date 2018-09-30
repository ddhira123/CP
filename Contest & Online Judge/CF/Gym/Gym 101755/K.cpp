#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int arr[N];
int n, m;

void read() {
  scanf("%d %d", &n, &m);
  for(int i = 0 ; i < n ; i++) {
    scanf("%d", &arr[i]);
  }
}

bool check(int k) {
  int i = 0;
  int x = 0;
  // cout << k;
  while (i < n) {
    if (arr[i] <= x) {
      i++;
      x++;
    } else if (k > 0) {
      k--;
      i++;
      x++;
    } else {
      i++;
    }
  }

  // cout << " " << x << endl;

  return x >= m;
}

void work() {
  // sort(arr, arr + n);

  int lo = 0, hi = n;
  while (lo < hi) {
    int mid = (lo + hi) / 2;

    if (check(mid)) hi = mid;
    else lo = mid+1;
  }

  printf("%d\n", lo);
}

int main() {
  read();
  work();
  return 0;
}