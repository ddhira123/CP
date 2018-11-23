#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;

vector<int> adj[N];
int sz[N];
int n;

int maxCrit;
int afterDes;

void dfs(int now, int prv) {
  int tot = 0;
  int split = 0;
  vector<int> v;

  sz[now] = 1;

  for (int nex : adj[now]) {
    if (nex == prv) continue;
    dfs(nex, now);

    split += tot * sz[nex];
    tot += sz[nex];

    sz[now] += sz[nex];
    v.push_back(sz[nex]);
  }

  v.push_back(n - sz[now]);
  split += tot * (n - sz[now]);

  if (split > maxCrit) {
    maxCrit = split;
    sort(v.begin(), v.end());

    afterDes = split - v[v.size()-2] * v[v.size()-1];
  }
}

int main() {
  scanf("%d", &n);
  n++;

  for (int i = 1 ; i < n ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1, -1);
  printf("%d %d\n", maxCrit, afterDes);
  return 0;
}