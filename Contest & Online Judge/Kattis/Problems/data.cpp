#include <bits/stdc++.h>
using namespace std;

const int N = 14;
const int VAL = 1000;

int primeFact[VAL * N + 5];

int dp[1 << N];
int sum[1 << N];
int arr[N];
int n;

void precompute() {
  for (int i = 2 ; i < VAL * N + 5 ; i++)
    if(primeFact[i] == 0)
      for (int j = i ; j < VAL * N + 5 ; j += i)
        primeFact[j]++;
}

int solve(int mask) {
  int &ret = dp[mask];
  if (ret != -1) return ret;
  ret = primeFact[sum[mask]];

  for (int i = mask & (mask-1) ; i > 0 ; i = mask & (i - 1)) {
    ret = max(ret, solve(i) + solve(mask - i));
  }

  return ret;
}

void read() {
  cin >> n;
  for(int i = 0 ; i < n ; i++) cin >> arr[i];
}

void prepare() {
  for (int i = 0 ; i < n ; i++) sum[1 << i] = arr[i];
  for (int i = 1 ; i < (1 << n) ; i++) {
    sum[i] = sum[i & -i] + sum[i - (i & -i)];
  }
  memset(dp, -1, sizeof dp);
}

int work() {
  return solve((1 << n) - 1);
}

int main() {
  precompute();
  read();
  prepare();
  printf("%d\n", work());
  return 0;
}