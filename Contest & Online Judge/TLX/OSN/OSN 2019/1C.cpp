#include <bits/stdc++.h>
using namespace std;

namespace Dinic {
  const int N = 1005;

  struct Edge {
    int from;
    int to;
    int flow;
  };

  vector<Edge> elist;
  vector<int> adj[3 * N * N];
  int dist[3 * N * N];
  int ptr[3 * N * N];
  bool reachFromSource[3 * N * N];

  int source, sink;
  int r, c;

  int getIn(int nr, int nc) {
    return (nr * c + nc) * 2;
  }

  int getOut(int nr, int nc) {
    return (nr * c + nc) * 2 + 1;
  }

  pair<int, int> getCell(int x) {
    x /= 2;
    return {x / c, x % c};
  }

  void addEdge(int from, int to, int flow) {
    adj[from].push_back(elist.size());
    elist.push_back((Edge){from, to, flow});

    adj[to].push_back(elist.size());
    elist.push_back((Edge){to, from, 0});
  }

  void createFlowGraph(vector<string> s, set<pair<int, int>> path) {
    r = s.size();
    c = s[0].size();

    source = getOut(r-1, c-1) + 1;
    sink = source + 1;

    for (int i = 0 ; i < r ; i++) {
      for (int j = 0 ; j < c ; j++) {
        if (path.count({i, j})) {
          if (i > 0 && s[i-1][j] == '.' && !path.count({i-1, j})) {
            addEdge(getOut(i-1, j), sink, 1);
          }
          if (i+1 < r && s[i + 1][j] == '.' && !path.count({i + 1, j})) {
            addEdge(source, getIn(i+1, j), 1);
          }
          if (j > 0 && s[i][j-1] == '.' && !path.count({i, j-1})) {
            addEdge(getOut(i, j-1), sink, 1);
          }
          if (j+1 < c && s[i][j+1] == '.' && !path.count({i, j+1})) {
            addEdge(source, getIn(i, j+1), 1);
          }
        } else if (s[i][j] == '.') {
          addEdge(getIn(i, j), getOut(i, j), 1);

          if (i+1 < r && s[i+1][j] == '.' && !path.count({i+1, j})) {
            addEdge(getOut(i, j), getIn(i+1, j), 1);
          }
          if (j+1 < c && s[i][j+1] == '.' && !path.count({i, j+1})) {
            addEdge(getOut(i, j), getIn(i, j+1), 1);
          }
        }
      }
    }
  }

  bool bfs() {
    memset(dist, -1, sizeof dist);
    dist[source] = 0;
    queue<int> q;
    q.push(source);

    while (!q.empty()) {
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

      if (dist[e.to] == dist[now] + 1 && e.flow > 0) {
        int cur = augment(e.to, min(f, e.flow));
        if (cur > 0) {
          elist[idx].flow -= cur;
          elist[idx ^ 1].flow += cur;
          return cur;
        }
      }
    }

    return 0;
  }

  int maxFlow() {
    int ret = 0;
    
    while (bfs()) {
      memset(ptr, 0, sizeof ptr);

      int cur = augment(source, 1e9);
      while (cur > 0) {
        ret += cur;
        // cerr << "sekarang " << ret << endl;
        cur = augment(source, 1e9);
      }
    }

    return ret;
  }

  void dfsFromSource(int now) {
    if (reachFromSource[now]) return;
    reachFromSource[now] = true;

    for (int idx : adj[now]) {
      Edge e = elist[idx];
      if (e.flow > 0) {
        dfsFromSource(e.to);
      }
    }
  }

  set<pair<int, int>> findMinCut() {
    memset(reachFromSource, 0, sizeof reachFromSource);
    dfsFromSource(source);

    set<pair<int, int>> ret;
    for (Edge e : elist) {
      if (reachFromSource[e.from] && !reachFromSource[e.to]) {
        // printf("%d %d\n", e.from, e.to);
        pair<int, int> cellFrom = getCell(e.from);
        pair<int, int> cellTo = getCell(e.to);

        if (cellFrom != cellTo && e.from != source) {
          // printf("(%d, %d) and (%d, %d)\n", cellFrom.first, cellFrom.second, cellTo.first, cellTo.second);
          // assert(false);
          continue;
        }

        ret.insert(cellTo);
      }
    }

    cerr << "ret.size() = " << ret.size() << endl;;

    return ret;
  }
}

vector<string> s;
string trail;
int r, c;

void read() {
  scanf("%d %d", &r, &c);
  cin >> trail;
  for (int i = 0 ; i < r ; i++) {
    string str;
    cin >> str;
    s.push_back(str);
  }
}

void prepare() {
  set<pair<int, int>> path = {{0, 0}};
  int nr = 0, nc = 0;

  for (char ch : trail) {
    if (ch == '>') nc++;
    else nr++;
    path.insert({nr, nc});
  }

  Dinic::createFlowGraph(s, path);
}

void work() {
  int mf = Dinic::maxFlow();
  // printf("%d\n", mf);
  cerr << "mf = " << mf << endl;

  set<pair<int, int>> cut = Dinic::findMinCut();
  for (auto it : cut) {
    s[it.first][it.second] = 'x';
  }

  for (auto str : s) {
    cout << str << endl;
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}
