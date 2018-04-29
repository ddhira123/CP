#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int MX = 100005;

int n, p;
int w[N], h[N];
int sum_wh;
double dp[MX];
bool ada[MX];

void read() {
  scanf("%d %d", &n, &p);
  sum_wh = 0;

  for(int i = 0 ; i < n ; i++) {
    scanf("%d %d", &w[i], &h[i]);
    sum_wh += 2 * (w[i] + h[i]);
  }
}

double work() {
  memset(ada, 0, sizeof ada);
  ada[0] = 1;
  dp[0] = 0;

  for(int i = 0 ; i < n ; i++) {
    int mins = 2 * min(w[i], h[i]);
    double maks = 2 * hypot(w[i], h[i]);

    double diff = maks - mins;
    for(int j = MX-1 ; j >= mins ; j--) {
      if(ada[j - mins]) {

        if(!ada[j]) {
          dp[j] = diff + dp[j - mins];
        } else {
          dp[j] = max(dp[j], diff + dp[j-mins]);
        }

        ada[j] = true;
      }
    }
  }

  double ret = 0;

  for(int i = 0 ; i < MX ; i++) {
    if(ada[i]) {
      int sums = sum_wh;
      sums += i;

      if(sums <= p) {
        double cur = sums;
        cur += dp[i];

        cur = min(cur, 1.0 * p);
        ret = max(ret, cur); 
      }
    }
  }

  return ret;
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    read();
    printf("Case #%d: %.9lf\n", tc, work());
  }
  return 0;
}