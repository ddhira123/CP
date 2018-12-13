#include <bits/stdc++.h>
using namespace std;

const int K = 302;

struct Edge {
  int from;
  int to;
  int flow;
};

vector<int> adj[K * K];
vector<Edge> elist;
int ptr[K * K];
int dist[K * K];
int k, n, m;

int source, sink;

int getVertex(int a, int b) {
  return a * k + b;
}

void addEdge(int from, int to, int flow) {
  adj[from].push_back(elist.size());
  elist.push_back((Edge){from, to, flow});
  adj[to].push_back(elist.size());
  elist.push_back((Edge){to, from, 0});
}

void init() {
  scanf("%d %d %d", &n, &k, &m);

  source = getVertex(n-1, k-1) + 1;
  sink = source+1;

  for (int i = 0 ; i < k ; i++) {
    addEdge(source, getVertex(i, i), 1);
  }

  for (int i = 0 ; i < k ; i++) {
    addEdge(getVertex(n-1, i), sink, 1e9);
  }

  for (int i = 0 ; i < m ; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    // u = rand() % n + 1;
    // v = rand() % n + 1;

    u--;
    v--;
    for (int j = 0 ; j < k ; j++) {
      int nj = (j + 1) % k;

      addEdge(getVertex(u, j), getVertex(v, nj), 1);
    }
  }
}

bool bfs() {
  for (int i = 0 ; i <= sink ; i++) dist[i] = -1;
  queue<int> q;
  q.push(source);
  dist[source] = 0;

  while(!q.empty()) {
    int now = q.front();
    q.pop();

    for (int idx : adj[now]) {
      Edge e = elist[idx];

      if (e.flow > 0 && dist[e.to] == -1) {
        dist[e.to] = dist[now] + 1;
        q.push(e.to);
      }
    }
  }

  return dist[sink] != -1;
}

int augment(int now, int f) {
  if (now == sink) return f;

  for (int &i = ptr[now] ; i < adj[now].size() ; i++) {
    int idx = adj[now][i];
    Edge e = elist[idx];

    if (e.flow > 0 && dist[e.to] == dist[now] + 1) {
      int res = augment(e.to, min(f, e.flow));
      if (res > 0) {
        elist[idx].flow -= res;
        elist[idx^1].flow += res;
        return res;
      }
    }
  }

  return 0;
}

int maxFlow() {
  int ret = 0;
  while (bfs()) {
    for (int i = 0 ; i <= sink ; i++)
      ptr[i] = 0;
    
    int f = augment(source, 1e9);
    while (f > 0) {
      ret += f;
      f = augment(source, 1e9);
    }
  }

  return ret;
}

int main() {
  init();
  printf("%d\n", maxFlow());
  return 0;
}