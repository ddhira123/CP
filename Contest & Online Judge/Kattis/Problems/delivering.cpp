#include <bits/stdc++.h>
using namespace std;

const int N = 1005;
const long long INF = 4e18;

int clientNum[N];
vector<pair<int, int>> adj[N];
long long dist[N];

vector<int> pathAdj[N];
int match[N];
bool vis[N];

int n, m, c;

void read() {
  scanf("%d %d %d", &n, &m, &c);
  for (int i = 1 ; i <= c ; i++) {
    int x; scanf("%d", &x);
    clientNum[x] = i;
  }
  for (int i = 0 ; i < m ; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);

    adj[u].push_back({v, w});
    // adj[v].push_back({u, w});
  }
}

void dijkstra() {
  priority_queue<pair<long long, int>> pq;

  for(int i = 0 ; i < n ; i++) dist[i] = INF;
  dist[0] = 0;
  pq.push({0, 0});

  while(!pq.empty()) {
    long long curDist = -pq.top().first;
    int now = pq.top().second;
    pq.pop();

    if (dist[now] != curDist) continue;

    for (pair<int, int> edge : adj[now]) {
      long long ndis = curDist + edge.second;
      int nex = edge.first;

      if (dist[nex] > ndis) {
        dist[nex] = ndis;
        pq.push({-ndis, nex});
      }
    }
  }
}

void dfs(int cli, int now) {
  if (vis[now]) return;
  vis[now] = 1;

  if (clientNum[now] != 0) pathAdj[cli].push_back(clientNum[now]);

  for (pair<int, int> edge: adj[now]) {
    if (edge.second + dist[now] == dist[edge.first])
      dfs(cli, edge.first);
  }
}

void prepare() {
  dijkstra();

  for (int i = 0 ; i < n ; i++) 
    if (clientNum[i] > 0) {
      memset(vis, 0, sizeof vis);

      dfs(clientNum[i], i);
      pathAdj[clientNum[i]].erase(pathAdj[clientNum[i]].begin());

      // printf("client %d:", clientNum[i]);
      // for (int nex : adj)
    }
}

int augment(int now) {
  if (vis[now]) return 0;
  vis[now] = 1;
  for (int nex : pathAdj[now])
    if (match[nex] == -1 || augment(match[nex])) {
      match[nex] = now;
      return 1;
    }
  return 0;
}

int mcbm() {
  memset(match, -1, sizeof match);
  int ret = 0;

  for (int i = 1 ; i <= c ; i++) {
    memset(vis, 0, sizeof vis);
    ret += augment(i);
  }

  return ret;
}

int work() {
  return c - mcbm();
}

int main() {
  read();
  prepare();
  printf("%d\n", work());
  return 0;
}