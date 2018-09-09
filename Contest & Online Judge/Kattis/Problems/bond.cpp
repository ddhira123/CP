#include <bits/stdc++.h>
using namespace std;

const int N = 20;

double dp[1 << N];
int arr[N][N];
int n;

void read() {
  scanf("%d", &n);
  for(int i = 0 ; i < n ; i++)
    for(int j = 0 ; j < n ; j++) {
      scanf("%d", &arr[i][j]);
    }
}

double work() {
  dp[0] = 1;
  for(int i = 1 ; i < (1 << n) ; i++) {
    int cur = n - __builtin_popcount(i);

    for(int j = 0 ; j < n ; j++) {
      if((1 << j) & i) {
        double val = arr[cur][j] / 100.0;
        dp[i] = max(dp[i], val * dp[i - (1 << j)]);
      }
    }
  }
  return dp[(1 << n) - 1] * 100;
}

int main() {
  read();
  printf("%.9lf\n", work());
  return 0;
}