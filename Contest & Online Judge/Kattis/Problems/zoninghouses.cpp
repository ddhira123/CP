#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int x[N], y[N];
int n, q;

struct SegmentTree {
  function<int(int, int)> f;
  int stree[4 * N];
  int n;

  void init(function<int(int, int)> fx, int _n) {
    f = fx;
    n = _n;

    build(1, 1, n);
  }

  void build(int id, int l, int r) {
    if(l == r) {
      stree[id] = l;
    } else {
      int m = (l + r) / 2;
      int chld = id << 1;
      
      build(chld, l, m);
      build(chld+1, m+1, r);

      stree[id] = f(stree[chld], stree[chld+1]);
    }
  }

  void remove(int x) {
    update(1, 1, n, x, -1);
  }

  void activate(int x) {
    update(1, 1, n, x, x);
  }

  void update(int id, int l, int r, int x, int val) {
    if(l == r) {
      stree[id] = val;
    } else {
      int m = (l + r) / 2;
      int chld = id << 1;

      if(x <= m) update(chld, l, m, x, val);
      else       update(chld+1, m+1, r, x, val);

      stree[id] = f(stree[chld], stree[chld+1]);
    }
  }

  int query(int l, int r) {
    return query(1, 1, n, l, r);
  }

  int query(int id, int l, int r, int x, int y) {
    if(x <= l && r <= y) {
      return stree[id];
    } else {
      int m = (l + r) / 2;
      int chld = id << 1;

      int ret = -1;
      if(x <= m) ret = f(ret, query(chld, l, m, x, y));
      if(y > m)  ret = f(ret, query(chld+1, m+1, r, x, y));

      return ret;
    }
  }
};

SegmentTree minX, maxX, minY, maxY;

void read() {
  scanf("%d %d", &n, &q);
  for(int i = 1 ; i <= n ; i++) {
    scanf("%d %d", &x[i], &y[i]);
  }
}

void prepare() {
  function<int(int, int)> fMinX = [&](int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
    if (x[a] == x[b]) return y[a] < y[b] ? a : b;
    return x[a] < x[b] ? a : b;
  };

  function<int(int, int)> fMaxX = [&](int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
    if (x[a] == x[b]) return y[a] > y[b] ? a : b;
    return x[a] > x[b] ? a : b;
  };

  function<int(int, int)> fMinY = [&](int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
    if (y[a] == y[b]) return x[a] < x[b] ? a : b;
    return y[a] < y[b] ? a : b;
  };

  function<int(int, int)> fMaxY = [&](int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
    if (y[a] == y[b]) return x[a] > x[b] ? a : b;
    return y[a] > y[b] ? a : b;
  };

  minX.init(fMinX, n);
  maxX.init(fMaxX, n);
  minY.init(fMinY, n);
  maxY.init(fMaxY, n);
}

int solve(int a, int b) {
  vector<int> points;
  points.push_back(minX.query(a, b));
  points.push_back(maxX.query(a, b));
  points.push_back(minY.query(a, b));
  points.push_back(maxY.query(a, b));

  int ret = 2e9;
  for(int point : points) {
    minX.remove(point); minY.remove(point); maxX.remove(point); maxY.remove(point);

    int xRange = x[maxX.query(a, b)] - x[minX.query(a, b)];
    int yRange = y[maxY.query(a, b)] - y[minY.query(a, b)];
    ret = min(ret, max(xRange, yRange));

    minX.activate(point); minY.activate(point); maxX.activate(point); maxY.activate(point);
  }

  return ret;
}

void work() {
  for(int i = 0 ; i < q ; i++) {
    int a, b;
    scanf("%d %d", &a, &b);

    printf("%d\n", solve(a, b));
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}