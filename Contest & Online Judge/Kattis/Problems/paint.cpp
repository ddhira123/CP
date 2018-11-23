#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

long long a[N], b[N];
vector<long long> uniq;

vector<int> adj[2 * N];
long long dp[2 * N];

long long n;
int k;

int getID(long long x) {
  return lower_bound(uniq.begin(), uniq.end(), x) - uniq.begin();
}

void read() {
  scanf("%lld %d", &n, &k);
  for (int i = 0 ; i < k ; i++) {
    scanf("%lld %lld", &a[i], &b[i]);
  }
}

void prepare() {
  for (int i = 0 ; i < k ; i++) {
    uniq.push_back(a[i]);
    uniq.push_back(b[i]+1);
  }

  sort(uniq.begin(), uniq.end());
  uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());

  for (int i = 0 ; i < k ; i++) {
    int aa = getID(a[i]);
    int bb = getID(b[i]+1);

    adj[aa].push_back(bb);
  }

  memset(dp, -1, sizeof dp);
}

long long solve(int now) {
  if (now == uniq.size()) return 0;

  long long &ret = dp[now];
  if (ret != -1) return ret;

  ret = solve(now+1);
  for (int nex : adj[now]) {
    ret = max(ret, solve(nex) + uniq[nex] - uniq[now]);
  }

  return ret;
}

long long work() {
  return n - solve(0);
}

int main() {
  read();
  prepare();
  printf("%lld\n", work());
  return 0;
}