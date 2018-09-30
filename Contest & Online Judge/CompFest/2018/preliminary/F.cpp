#include <bits/stdc++.h>
using namespace std;

const int N = 2005;
const long long INF = 4e18;

int a[N];
int r[N];
int d[N];
long long sumD[N];
int n, k, l;
long long dp_back[N][N];
long long dp_front[N][N];

void prepare() {
  for(int i = 2 ; i <= n ; i++) {
    sumD[i] = sumD[i-1] + d[i];
  }
}

void rev() {
  reverse(a + 1, a + n + 1);
  reverse(r + 1, r + n + 1);
  reverse(d + 2, d + n + 1);
}

void solve_backward() {
  for(int i = 1 ; i <= n ; i++) {
    dp_back[1][i] = r[i];
  }
  for(int i = 2 ; i <= k ; i++) {
    deque<pair<long long, long long>> dq;

    for(int j = n ; j >= 1 ; j--) {
      dp_back[i][j] = -INF;

      while(!dq.empty() && dq.front().second - sumD[j] > l) {
        // printf("i %d j %d popping %lld - %lld\n", i, j, dq.front().second, sumD[j]);
        dq.pop_front();
      }
      
      if(!dq.empty()) {
        dp_back[i][j] = dq.front().first + r[j] + 2 * sumD[j];
      }

      pair<long long, long long> tmp = {dp_back[i - 1][j] - 2 * sumD[j],
                                        sumD[j]};

      // printf("")
      while (!dq.empty() && dq.back() <= tmp) dq.pop_back();
      dq.push_back(tmp);
    }
  }
}

void solve_forward() {
  for (int i = 1; i <= n; i++) {
    dp_front[1][i] = r[i];
  }

  for (int i = 2; i <= k; i++) {
    deque<pair<long long, long long>> dq;

    for (int j = 1; j <= n; j++) {
      dp_front[i][j] = -INF;

      while (!dq.empty() && sumD[j] - dq.front().second > l) dq.pop_front();

      if (!dq.empty()) {
        dp_front[i][j] = dq.front().first + r[j] - sumD[j];
      }

      pair<long long, long long> tmp = {dp_front[i - 1][j] + sumD[j],
                                        sumD[j]};

      while (!dq.empty() && dq.back() <= tmp) dq.pop_back();
      dq.push_back(tmp);
    }
  }
}

void read() {
  scanf("%d %d %d", &n, &k, &l);
  for(int i = 1 ; i <= n ; i++) scanf("%d", &a[i]);
  for(int i = 1 ; i <= n ; i++) scanf("%d", &r[i]);
  for(int i = 2 ; i <= n ; i++) scanf("%d", &d[i]);
}

long long work() {
  long long ret = 0;

  
  for(int it = 0 ; it < 2 ; it++) {
    prepare();
    solve_forward();
    solve_backward();

    // for (int i = 1; i <= k; i++)
    //   for (int j = 1; j <= n; j++)
    //     printf("i %d j %d fr %lld bk %lld\n", i, j, dp_front[i][j],
    //            dp_back[i][j]);

    long long bk[N], mx[N];
    for(int i = 1 ; i <= n ; i++) {
      bk[i] = -INF;
      mx[i] = dp_front[k][i];
    }

    for(int j = k-1 ; j >= 1 ; j--) {
      for(int i = 1 ; i <= n ; i++) {
        bk[i] = max(bk[i], dp_back[k - j + 1][i]);
        mx[i] = max(mx[i], dp_front[j][i]);

        // if(i == 2) {
        //   printf("j %d res %lld\n", j, dp_front[j][i] + bk[i] - r[i] - a[i]);
        // }
        ret = max(ret, dp_front[j][i] + bk[i] - r[i] - a[i]);
      }
    }

    for(int i = 1 ; i <= n ; i++)
      ret = max(ret, mx[i] - a[i]);
    
    // for(int j = 1 ; j <= k ; j++)

    // for(int i = 1 ; i <= n ; i++) {
    //   for(int j = 1 ; j <= k ; j++) {
    //     // printf("i %d j %d asd %lld\n", i, j, dp_front[j][i] - a[i]);
    //     ret = max(ret, dp_front[j][i] - a[i]);
    //   }
    //   long long bk = -INF;

    //   for(int j = k-1 ; j >= 1 ; j--) {
    //     bk = max(bk, dp_back[k - j + 1][i]);

    //     ret = max(ret, dp_front[j][i] + bk - r[i] - a[i]);
    //   }
    // }

    // printf("it -> %d ret %lld\n", it, ret);
    rev();
  }

  return ret;
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    read();
    printf("%lld\n", work());
  }
  return 0;
}