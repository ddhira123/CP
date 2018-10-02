#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> adj[N];
int val[N];
long long dp[N];
bool dp_set[N];
int n, m, k, sa, sb;

void read() {
  scanf("%d %d %d %d %d", &n, &m, &k, &sa, &sb);
  for (int i = 0 ; i < m ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    adj[u].push_back(v);
  }
  for (int i = 1 ; i <= n ; i++) {
    char opt[11];
    scanf("%s", opt);

    if (opt[0] == 'S') {
      scanf("%d", &val[i]);
    } else if(opt[0] == 'T') {
      scanf("%d", &val[i]);
      val[i] = -val[i];
    } else {
      int x, y;
      scanf("%d %d", &x, &y);
    }
  }

  // for (int i = 1 ; i <= n ; i++) {
  //   printf("i %d val %d\n", i, val[i]);
  // }
}

long long solve(int now) {
  if (dp_set[now]) return dp[now];
  
  dp_set[now] = 1;
  long long &ret = dp[now];
  ret = adj[now].empty() ? 0 : -4e18;

  for (int nex : adj[now])
    ret = max(ret, solve(nex));
  ret += val[now];

  return ret;
}

int main() {
  read();
  printf("%lld %lld\n", solve(sa) - val[sa], solve(sb) - val[sb]);
  return 0;
}