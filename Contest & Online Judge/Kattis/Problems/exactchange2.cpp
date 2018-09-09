#include <bits/stdc++.h>
using namespace std;

const int MX = 1e4 + 5;
const int N = 105;

int dp[MX];
int n, tgt;
int arr[N];

void read() {
  scanf("%d %d", &tgt, &n);
  for(int i = 0 ; i < n ; i++) {
    scanf("%d", &arr[i]);
  }
}

void DP() {
  memset(dp, -1, sizeof dp);

  dp[0] = 0;
  for(int i = 0 ; i < n ; i++) {
    for(int j = MX-1 ; j >= arr[i] ; j--) {
      if(dp[j - arr[i]] != -1) {
        if(dp[j] == -1) {
          dp[j] = dp[j - arr[i]] + 1;
        } else {
          dp[j] = min(dp[j], dp[j - arr[i]] + 1);
        }
      }
    }
  }
}

void work() {
  DP();

  for(int i = tgt ; ; i++) {
    if(dp[i] != -1) {
      printf("%d %d\n", i, dp[i]);
      return;
    }
  }
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    read();
    work();
  }
  return 0;
}