#include <bits/stdc++.h>
using namespace std;

const int N = 5005;

long long dp[2][N];
int n, k;
int arr[N];
long long psum[N];

void read() {
  scanf("%d %d", &n, &k);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &arr[i]);

    psum[i] = arr[i] + psum[i-1];
  }
}

long long DP() {
  for (int i = 1 ; i <= n ; i++)
    dp[0][i] = -4e18;
  
  for (int i = 1 ; i <= k ; i++) {
    int bit = i & 1;
    int prv = bit ^ 1;

    long long maxDP = dp[prv][0];
    long long maxPrv = -4e18;
    dp[bit][0] = -4e18;

    for (int i = 1 ; i <= n ; i++) {
      maxPrv = max(maxPrv, maxDP - psum[i-1]);
      maxDP = max(maxDP, dp[prv][i]);

      dp[bit][i] = maxPrv + psum[i];
    }
  }

  long long ret = -4e18;
  for (int i = 1 ; i <= n ; i++)
    ret = max(ret, dp[k & 1][i]);
  
  return ret;
}

int main() {
  read();
  printf("%lld\n", DP());
  return 0;
}