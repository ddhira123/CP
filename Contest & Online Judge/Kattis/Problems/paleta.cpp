#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

int dp[N][2];
int f[N];
int deg[N];
int n, k;

void read() {
  scanf("%d %d", &n, &k);
  for(int i = 1 ; i <= n ; i++) {
    scanf("%d", &f[i]);
  }
}

void prepare() {
  for(int i = 1 ; i <= n ; i++) {
    deg[f[i]]++;
  }

  dp[1][0] = k;
  dp[1][1] = 0;

  for(int i = 2 ; i <= n ; i++) {
    dp[i][0] = dp[i-1][1];

    dp[i][1] = (1ll * dp[i-1][0] * (k-1)) % MOD;
    if(k > 1) {
      dp[i][1] = (dp[i][1] + 1ll * dp[i-1][1] * (k-2)) % MOD;
    }
  }
}

int work() {
  int ret = 1;
  queue<int> q;

  for(int i = 1 ; i <= n ; i++) {
    if(deg[i] == 0) {
      q.push(i);
    }
  }

  while(!q.empty()) {
    int now = q.front();
    q.pop();

    ret = 1ll * ret * (k - 1) % MOD;
    deg[f[now]]--;

    if(deg[f[now]] == 0) {
      q.push(f[now]);
    }
  }

  for(int i = 1 ; i <= n ; i++) {
    if(deg[i] > 0) {
      int cur = i;
      int sz = 0;

      do {
        deg[cur] = 0;
        sz++;

        cur = f[cur];
      } while(cur != i);

      if(sz == 1) {
        ret = 1ll * ret * k % MOD;
      } else {
        ret = 1ll * ret * dp[sz][1] % MOD;
      }
    }
  }

  return ret;
}

int main() {
  read();
  prepare();
  printf("%d\n", work());
  return 0;
}