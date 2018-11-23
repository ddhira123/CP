#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;

int pset[N];

int finds(int x) {
  return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

void join(int x, int y) {
  x = finds(x);
  y = finds(y);

  if (x != y) {
    pset[x] += pset[y];
    pset[y] = x;
  }
}

struct Edge {
  int u, v;
  double w;
};

int n, e, p;
double x[N], y[N];
int u[N], v[N];
vector<Edge> elist;

void read() {
  scanf("%d %d %d", &n, &e, &p);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%lf %lf", &x[i], &y[i]);
  }
  for (int i = 0 ; i < p ; i++) {
    scanf("%d %d", &u[i], &v[i]);
  }
}

void prepare() {
  memset(pset, -1, sizeof pset);

  for (int i = 1 ; i <= e ; i++) {
    join(i, 1);
  }

  for (int i = 0 ; i < p ; i++) {
    join(u[i], v[i]);
  }

  for (int i = 1 ; i <= n ; i++)
    for (int j = i+1 ; j <= n ; j++)
      if (finds(i) != finds(j)) {
        elist.push_back((Edge){i, j, hypot(x[i] - x[j], y[i] - y[j])});
      }
  
  sort(elist.begin(), elist.end(), [](Edge a, Edge b) {
    return a.w < b.w;
  });
}

double work() {
  double ret = 0;
  for (Edge edge : elist) {
    if (finds(edge.u) != finds(edge.v)) {
      join(edge.u, edge.v);
      ret += edge.w;
    }
  }
  return ret;
}

int main() {
  read();
  prepare();
  printf("%.9lf\n", work());
  return 0;
}