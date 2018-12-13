#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x;
  int y;

  void read() {
    // x = rand() % 40000000;
    // y = rand() % 40000000;
    scanf("%d %d", &x, &y);
  }

  bool operator <(Point other) const {
    return x != other.x ? x < other.x : y < other.y;
  }

  bool operator ==(Point other) const {
    return x == other.x && y == other.y;
  }
};

const int N = 5005;

long long getArea(Point a, Point b, Point c) {
  long long ret = 1ll * a.x * b.y + 1ll * b.x * c.y + 1ll * c.x * a.y;
  ret -= (1ll * a.y * b.x + 1ll * b.y * c.x + 1ll * c.y * a.x);

  return abs(ret);
}

long long cross(Point p, Point q, Point r) {
  long long dx1 = q.x - p.x;
  long long dy1 = q.y - p.y;
  long long dx2 = r.x - p.x;
  long long dy2 = r.y - p.y;

  return dx1 * dy2 - dx2 * dy1;
}

long long sqr(long long z) {
  return z * z;
}

long long squaredDist(Point p, Point q) {
  return sqr(p.x - q.x) + sqr(p.y - q.y);
}

vector<Point> convexHull(Point v[], int n) {
  sort(v, v + n);
  Point pivot = v[0];
  sort(v + 1, v + n, [&](Point a, Point b) {
    if (cross(pivot, a, b) == 0) {
      return squaredDist(pivot, a) < squaredDist(pivot, b);
    }

    return cross(pivot, a, b) > 0;
  });

  vector<Point> ret;
  for (int i = 0 ; i < n ; i++) {
    while(ret.size() >= 2 && cross(ret[ret.size()-2], ret.back(), v[i]) < 0) {
      ret.pop_back();
    }
    ret.push_back(v[i]);
  }
  return ret;
}

Point arr[N];
Point temp[N];
int n;

void init() {
  cin >> n;
  for (int i = 0 ; i < n ; i++)
    arr[i].read();
  
  sort(arr, arr + n);

  int nn = 0;
  for (int i = 0 ; i < n ; i++)
    if (nn == 0 || !(arr[i] == temp[nn-1])) {
      temp[nn++] = arr[i];
    }
  
  for (int i = 0 ; i < nn ; i++)
    arr[i] = temp[i];
  n = nn;
}

long long work() {
  long long ret = 0;
  vector<Point> hull = convexHull(arr, n);

  // printf("%d\n", hull.size());

  int sz = hull.size();
  for (int i = 0 ; i < hull.size() ; i++) {
    int it = i;
    for (int j = i+1 ; j < hull.size() ; j++) {
      while (getArea(hull[i], hull[j], hull[it]) < getArea(hull[i], hull[j], hull[(it + 1) % sz])) {
        it = (it + 1) % sz;
      }

      ret = max(ret, getArea(hull[i], hull[j], hull[it]));
    }
  }
  return ret;
}

int main() {
  init();
  
  long long area = work();
  printf("%lld.%lld\n", area / 2, (area % 2) * 5);
  return 0;
}