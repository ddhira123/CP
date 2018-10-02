#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int arr[N];
int cnt[N];
long long prefixSum[N];
int n, k;

void read() {
  scanf("%d %d", &n, &k);
  for(int i = 0 ; i < k ; i++) {
    int x; scanf("%d", &x);
    cnt[x]++;
  }
}

void prepare() {
  for(int jump = 1 ; jump < N ; jump++)
    for(int i = 0 ; i < N ; i += jump)
      arr[i] += cnt[jump];
  
  prefixSum[0] = arr[0];
  for(int i = 1 ; i < N ; i++)
    prefixSum[i] = arr[i] + prefixSum[i-1];
}

void work() {
  int q; scanf("%d", &q);
  for(int i = 0 ; i < q ; i++) {
    int l, r;
    scanf("%d %d", &l, &r);

    long long ret = prefixSum[r] - (l ? prefixSum[l-1] : 0);
    printf("%lld\n", ret);
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}