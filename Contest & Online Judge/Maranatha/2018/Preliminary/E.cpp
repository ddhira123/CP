#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

struct Point {
  int x, y;

  void read() {
    scanf("%d %d", &x, &y);
  }
};

struct Circle {
  double x, y, r;
};

Point arr[N];
int n;

Circle rec(vector<Point> p, vector<Point> r) {
  // printf("%d %d\n", p.size(), r.size());
  if(p.empty() || r.size() >= 3) {
    if(r.empty()) return (Circle){-1, -1, -1};
    if(r.size() == 1) {
      return (Circle){r[0].x, r[0].y, 0};
    }
    if(r.size() == 2) {
      double mx = 1.0 * (r[0].x + r[1].x) / 2;
      double my = 1.0 * (r[0].y + r[1].y) / 2;
      double dst = hypot(r[0].x - r[1].x, r[0].y - r[1].y) / 2;

      return (Circle){mx, my, dst};
    }

    long long x1, x2, x3, y1, y2, y3;
    x1 = r[0].x, x2 = r[1].x, x3 = r[2].x;
    y1 = r[0].y, y2 = r[1].y, y3 = r[2].y;

    long long A = x1 * (y2 - y3) - y1 * (x2 - x3) + x2 * y3 - x3 * y2;
    if(A == 0) return (Circle){-1, -1, -1};
    long long B = (x1 * x1 + y1 * y1) * (y3 - y2) +
                  (x2 * x2 + y2 * y2) * (y1 - y3) +
                  (x3 * x3 + y3 * y3) * (y2 - y1);
    long long C = (x1 * x1 + y1 * y1) * (x2 - x3) +
                  (x2 * x2 + y2 * y2) * (x3 - x1) +
                  (x3 * x3 + y3 * y3) * (x1 - x2);
    long long D = (x1 * x1 + y1 * y1) * (x3 * y2 - x2 * y3) +
                  (x2 * x2 + y2 * y2) * (x1 * y3 - x3 * y1) +
                  (x3 * x3 + y3 * y3) * (x2 * y1 - x1 * y2);
    
    double x = -1.0 * B / (2 * A);
    double y = -1.0 * C / (2 * A);
    double r = sqrt((1.0 * B * B + 1.0 * C * C - 4.0 * A * D) / (4.0 * A * A));

    return (Circle){x, y, r};
  }

  Point cur = p.back();
  p.pop_back();
  
  Circle c = rec(p, r);
  if(hypot(cur.x - c.x, cur.y - c.y) < c.r + 1e-9)
    return c;
  r.push_back(cur);

  return rec(p, r);
}

int main() {
  int t; cin >> t;

  for(int tc = 1 ; tc <= t ; tc++) {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
      // arr[i].x = rand() % 1000;
      // arr[i].y = rand() % 1000;
      arr[i].read();
    }

    vector<Point> p, r;
    for(int i = 0 ; i < n ; i++) p.push_back(arr[i]);

    random_shuffle(p.begin(), p.end());
    Circle ret = rec(p, r);

    printf("%.2lf %.2lf %.2lf\n", ret.x, ret.y, ret.r);
  }
  return 0;
}