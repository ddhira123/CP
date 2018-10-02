#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Dinic {
  static const int N = 10005;

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
    elist.push_back((Edge){to, from, 0});

    // printf("add edge %d -> %d flow %d\n", from, to, flow);
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
int n;
int a, b, c;
int ga, gb;

void init() {
  scanf("%d", &n);
  scanf("%d %d", &ga, &gb);
  scanf("%d %d %d", &a, &b, &c);
  
  int source = 2 * n + ga + gb;
  int sink = source + 1;
  network = Dinic(source, sink, sink);

  for (int i = 0 ; i < n ; i++) {
    network.add_edge(i, n + i, c);
  }

  for (int i = 0 ; i < ga ; i++) {
    int group_id = i + 2 * n;

    int sz; scanf("%d", &sz);
    network.add_edge(source, group_id, a);

    for (int j = 0 ; j < sz ; j++) {
      int id; scanf("%d", &id);
      id--;

      network.add_edge(group_id, id, INF);
    }
  }

  for (int i = 0 ; i < gb ; i++) {
    int group_id = ga + i + 2 * n;

    int sz; scanf("%d", &sz);
    network.add_edge(group_id, sink, b);

    for (int j = 0; j < sz; j++) {
      int id;
      scanf("%d", &id);
      id--;

      network.add_edge(id + n, group_id, INF);
    }
  }
}

int main() {
  init();
  printf("%d\n", network.maxFlow());
  return 0;
}