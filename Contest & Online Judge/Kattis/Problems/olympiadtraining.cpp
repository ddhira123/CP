#include <bits/stdc++.h>
using namespace std;

const int N = 20;
const int M = 10001;

int n, m, q;
int arr[N][M];

long long all;
long long dp[1 << N];
long long ans[N + 5];

void read() {
  scanf("%d %d %d", &n, &m, &q);
  for (int i = 0 ; i < n ; i++)
    for (int j = 0 ; j < m ; j++)
      scanf("%d", &arr[i][j]);
}

void prepare() {
  memset(dp, 0, sizeof dp);
  for (int i = 0 ; i <= n ; i++) {
    ans[i] = 4e18;
  }
  all = 0;

  for (int j = 0 ; j < m ; j++) {
    vector<pair<int, int>> v;
    for (int i = 0 ; i < n ; i++) {
      v.push_back({arr[i][j], i});
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());

    all += v[0].first;
    int msk = 0;
    for (int i = 0 ; i+1 < v.size() ; i++) {
      msk |= (1 << v[i].second);
      dp[msk] += (-v[i].first + v[i+1].first);
    }
  }

  for (int i = 0 ; i < n ; i++)
    for (int msk = 0 ; msk < (1 << n) ; msk++)
      if (msk & (1 << i))
        dp[msk] += dp[msk ^ (1 << i)];
  
  for (int msk = 0 ; msk < (1 << n) ; msk++) {
    int active = n - __builtin_popcount(msk);
    ans[active] = min(ans[active], all + dp[msk]);
  }
}

void work() {
  for (int i = 0 ; i < q ; i++) {
    int x; scanf("%d", &x);
    printf("%lld\n", ans[x]);
  }
}

int main() {
  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    read();
    prepare();
    work();
  }
  return 0;
}