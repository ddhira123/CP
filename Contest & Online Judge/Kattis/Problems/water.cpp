#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

struct Dinic {
  struct Edge {
    int from;
    int to;
    int flow;
  };

  vector<Edge> elist;
  vector<int> adj[N];
  int saiz;

  int ptr[N];
  int dist[N];

  int source, sink;
  int num;

  Dinic(int _s = 0, int _t = 0, int _num = 0) {
    source = _s;
    sink = _t;
    num = _num;
    reset();
  }

  void reset() {
    for (int i = 0; i <= num; i++) adj[i].clear();
    elist.clear();
    saiz = 0;
  }

  void add_edge(int from, int to, int flow) {
    adj[from].push_back(saiz++);
    adj[to].push_back(saiz++);

    elist.push_back((Edge){from, to, flow});
    elist.push_back((Edge){to, from, flow});
  }

  bool BFS() {
    for (int i = 0; i <= num; i++) dist[i] = -1;
    queue<int> q;
    q.push(source);
    dist[source] = 0;

    while (!q.empty() && dist[sink] == -1) {
      int now = q.front();
      q.pop();
      for (int idx : adj[now]) {
        int to = elist[idx].to;
        int flow = elist[idx].flow;

        if (dist[to] == -1 && flow > 0) {
          dist[to] = dist[now] + 1;
          q.push(to);
        }
      }
    }

    return dist[sink] != -1;
  }

  int augment(int now, int f) {
    if (now == sink) return f;

    for (int &i = ptr[now]; i < adj[now].size(); i++) {
      int idx = adj[now][i];
      int to = elist[idx].to;
      int flow = elist[idx].flow;

      if (dist[to] == dist[now] + 1 && flow > 0) {
        int res = augment(to, min(f, flow));
        if (res > 0) {
          elist[idx].flow -= res;
          elist[idx ^ 1].flow += res;
          return res;
        }
      }
    }

    return 0;
  }

  int maxFlow() {
    int mf = 0;
    while (BFS()) {
      for (int i = 0; i <= num; i++) ptr[i] = 0;
      int add = augment(source, (int)1e9);
      while (add > 0) {
        mf += add;
        add = augment(source, (int)1e9);
      }
    }
    return mf;
  }
};

Dinic network;
int n, p, k;

int main() {
  scanf("%d %d %d", &n, &p, &k);

  network = Dinic(1, 2, n);
  for (int i = 0 ; i < p ; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    network.add_edge(a, b, c);
  }

  int ret = network.maxFlow();
  printf("%d\n", ret);

  for (int i = 0 ; i < k ; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    network.add_edge(a, b, c);

    ret += network.maxFlow();
    printf("%d\n", ret);
  }

  return 0;
}