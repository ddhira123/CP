#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int cnt[N];

int main() {
  int n; scanf("%d", &n);
  for(int i = 0 ; i < n ; i++) {
    int x; scanf("%d", &x);
    cnt[x]++;
  }

  int ret = 0;
  for(int i = 0 ; i < N ; i++)
    ret += cnt[i] / 2;
  
  printf("%d\n", ret / 2);
  return 0;
}