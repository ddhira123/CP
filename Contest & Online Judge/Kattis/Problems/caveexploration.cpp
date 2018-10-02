#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

vector<int> adj[N];
vector<pair<int, int>> adjTree[N];

int num[N], low[N];

int n, m;

void tarjan(int pre, int now) {
  static int cnt = 1;
  num[now] = low[now] = cnt++;

  for (int nex : adj[now]) {
    if (num[nex] == 0) {
      tarjan(now, nex);

      int val = 0;
      if (low[nex] > num[now]) {
        val = 1;
      }

      adjTree[now].push_back({nex, val});
      adjTree[nex].push_back({now, val});

      low[now] = min(low[now], low[nex]);
    } else if (nex != pre) {
      low[now] = min(low[now], num[nex]);
    }
  }
}

void read() {
  scanf("%d %d", &n, &m);
  for (int i = 0 ; i < m ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);

    adj[u].push_back(v);
    adj[v].push_back(u);
  }
}

int dfs(int pre, int now) {
  int ret = 1;

  for (auto it : adjTree[now]) {
    if (it.first != pre && it.second == 0) {
      ret += dfs(now, it.first);
    }
  }

  return ret;
}

int work() {
  tarjan(-1, 0);
  return dfs(-1, 0);
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}