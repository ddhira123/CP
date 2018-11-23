#include <bits/stdc++.h>
using namespace std;

const int GRID = 35;
const int INF = 1e9;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

struct Edge {
  int from;
  int to;
  int flow;
};

char s[GRID][GRID];
vector<Edge> elist;
vector<int> adj[GRID * GRID * 2];
int dist[GRID * GRID * 2];
int ptr[GRID * GRID * 2];
int n, m, ch;
int val[27];

int getCellNum(int r, int c) { return r * m + c; }

int getIn(int r, int c) { return 2 * getCellNum(r, c) + 1; }

int getOut(int r, int c) { return 2 * getCellNum(r, c) + 2; }

void addEdge(int from, int to, int flow) {
  adj[from].push_back(elist.size());
  elist.push_back((Edge){from, to, flow});

  adj[to].push_back(elist.size());
  elist.push_back((Edge){to, from, 0});

  // printf("%d %d %d\n", from, to, flow);
}

int source;
int sink;
int num;

void read() {
  // n = 30;
  // m = 30;
  // ch = 26;
  // for (int i = 0 ; i < n ; i++)
  //     for (int j = 0 ; j < m ; j++) {
  //         int v = rand() % 27;
  //         s[i][j] = v == 26 ? '.' : 'a' + v;
  //     }
  // for (int i = 0 ; i < ch ; i++) {
  //     val[i] = rand() % 100000;
  // }

  // s[rand() % n][rand() % m] = 'B';
  scanf("%d %d %d", &n, &m, &ch);
  swap(n, m);
  for (int i = 0; i < n; i++) {
    scanf("%s", s[i]);
  }
  for (int i = 0; i < ch; i++) {
    scanf("%d", &val[i]);
  }
}

void prepare() {
  sink = 0;
  num = getOut(n - 1, m - 1);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      if (s[i][j] == 'B') {
        addEdge(getIn(i, j), getOut(i, j), INF);
        source = getIn(i, j);
      } else if (s[i][j] != '.') {
        addEdge(getIn(i, j), getOut(i, j), val[s[i][j] - 'a']);
      } else {
        addEdge(getIn(i, j), getOut(i, j), INF);
      }

      for (int k = 0; k < 4; k++) {
        int ni = i + dr[k];
        int nj = j + dc[k];

        int nex = sink;
        if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
          nex = getIn(ni, nj);
        }

        addEdge(getOut(i, j), nex, INF);
      }
    }
}

bool bfs() {
  for (int i = 0; i <= num; i++) {
    dist[i] = -1;
  }

  queue<int> q;
  q.push(sink);
  dist[sink] = 0;

  while (!q.empty()) {
    int now = q.front();
    q.pop();

    for (int idx : adj[now]) {
      Edge edge = elist[idx];
      int otherFlow = elist[idx ^ 1].flow;

      if (dist[edge.to] == -1 && otherFlow > 0) {
        dist[edge.to] = dist[now] + 1;
        q.push(edge.to);
      }
    }
  }

  return dist[source] != -1;
}

int augment(int now, int f) {
  if (now == sink) return f;

  for (int &i = ptr[now]; i < adj[now].size(); i++) {
    int idx = adj[now][i];
    Edge edge = elist[idx];

    if (edge.flow > 0 && dist[edge.to] == dist[now] - 1) {
      int res = augment(edge.to, min(f, edge.flow));

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
  int ret = 0;
  while (bfs()) {
    for (int i = 0; i <= num; i++) {
      ptr[i] = 0;
    }
    int res = augment(source, INF);

    while (res > 0) {
      ret += res;
      res = augment(source, INF);
    }
  }
  return ret;
}

int main() {
  srand(time(NULL));

  read();
  prepare();
  int ret = maxFlow();

  if (ret == INF) ret = -1;

  cout << ret << endl;
  return 0;
}