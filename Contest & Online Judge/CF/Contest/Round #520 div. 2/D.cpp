#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

vector<int> adj[N];
int n;

bool vis[N];

int getVal(int x, int y) {
  if (x < y) swap(x, y);
  return x / y;
}

long long dfs(int now) {
  vis[now] = 1;

  long long ret = 0;
  for (int nex : adj[now]) {
    ret += getVal(now, nex);
    if (!vis[nex]) {
      ret += dfs(nex);
    }
  }

  return ret;
}

int main() {
  cin >> n;
  for (int i = 2 ; i <= n ; i++)
    for (int j = 2 * i ; j <= n ; j += i) {
      adj[i].push_back(j);
      adj[j].push_back(i);
    }
  
  long long ret = 0;
  for (int i = 2 ; i <= n ; i++)
    if (!vis[i])
      ret = max(ret, dfs(i));
  
  printf("%lld\n", ret * 2);
  return 0;
}