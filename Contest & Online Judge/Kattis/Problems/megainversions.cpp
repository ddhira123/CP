#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

long long BIT[3][N];
int arr[N];
int n;

void update(int id, int x, long long val) {
  for (; x <= n ; x += x & -x) {
    BIT[id][x] += val;
  }
}

long long query(int id, int x) {
  long long ret = 0;
  while (x) {
    ret += BIT[id][x];
    x -= x & -x;
  }
  return ret;
}

int main() {
  scanf("%d", &n);
  for (int i = 0 ; i < n ; i++) scanf("%d", &arr[i]);

  for (int i = n-1 ; i >= 0 ; i--) {
    int num = arr[i];

    update(0, num, 1);
    update(1, num, query(0, num-1));
    update(2, num, query(1, num-1));
  }

  long long ret = query(2, n);
  printf("%lld\n", ret);
  
  return 0;
}