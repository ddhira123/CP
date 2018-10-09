#include <bits/stdc++.h>
using namespace std;

const int N = 16;

int x[N], y[N];
double dp[N][1 << N];
double dis[N][N];
bool done[N][1 << N];
int n;

double solve(int lst, int mask) {
  if (mask == (1 << n)-1) return 0;
  if (done[lst][mask]) return dp[lst][mask];

  double &ret = dp[lst][mask];
  done[lst][mask] = 1;

  ret = 4e18;
  int active = __builtin_popcount(mask);

  for (int i = 0 ; i < n ; i++) {
    if ((mask & (1 << i)) == 0) {
      double r = dis[lst][i];
      ret = min(ret, r * active + solve(i, mask | (1 << i)));
    }
  }

  return ret;
}

int main() {
  scanf("%d", &n);
  for (int i = 0 ; i < n ; i++)
    scanf("%d %d", &x[i], &y[i]);
  
  for (int i = 0 ; i < n ; i++)
    for (int j = 0 ; j < n ; j++)
      dis[i][j] = hypot(x[i] - x[j], y[i] - y[j]);

  double ret = 4e18;
  for (int i = 0 ; i < n ; i++)
    ret = min(ret, solve(i, 1 << i));
  
  printf("%.9lf\n", ret);
  return 0;
}