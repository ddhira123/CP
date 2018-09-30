#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n;
int arr[N];
int dp[N];

void read() {
  scanf("%d", &n);
  for(int i = 1 ; i <= n ; i++) scanf("%d", &arr[i]);
}

int solve(int now) {
  int &ret = dp[now];
  if (ret != -1) return ret;

  ret = 0;
  for(int i = 2 ; i <= 5 ; i++) {
    if(now + i <= n)
      ret = max(ret, solve(now + i));
  }

  ret += arr[now];
  return ret;
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    read();
    memset(dp, -1, sizeof dp);
    int ret = solve(0);

    printf("Case %d :%d\n", tc, ret);
  }
  return 0;
}