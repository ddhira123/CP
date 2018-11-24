#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

vector<pair<int, pair<int, int>>> adj[N];
long long dist[N];
bool vis[N];
int n, m, k;

void read() {
  scanf("%d %d %d", &n, &m, &k);

  for (int i = 1 ; i <= m ; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);

    adj[u].push_back({i, {v, w}});
    adj[v].push_back({i, {u, w}});
  }
}

void dijkstra() {
  for (int i = 1 ; i <= n ; i++) {
    dist[i] = 4e18;
  }

  dist[1] = 0;
  priority_queue<pair<long long, int>> pq;
  pq.push({0, 1});

  while(!pq.empty()) {
    long long dst = -pq.top().first;
    int cur = pq.top().second;
    pq.pop();

    if (dist[cur] != dst) continue;

    for (auto it : adj[cur]) {
      int nex = it.second.first;
      long long ndis = dst + it.second.second;

      if (ndis < dist[nex]) {
        dist[nex] = ndis;
        pq.push({-ndis, nex});
      }
    }
  }
}

vector<int> ans;

void dfs(int now) {
  vis[now] = 1;

  for (auto it : adj[now]) {
    int idx = it.first;
    int nex = it.second.first;
    
    if (k > 0 && !vis[nex] && it.second.second + dist[now] == dist[nex]) {
      k--;
      ans.push_back(idx);
      dfs(nex);
    }
  }
}

void work() {
  dijkstra();
  dfs(1);

  printf("%d\n", (int)ans.size());
  for (int x : ans) printf("%d ", x);
}

int main() {
  read();
  work();
  return 0;
}