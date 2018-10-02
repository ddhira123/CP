#include <bits/stdc++.h>
using namespace std;

const int N = 255;

int bx[N], by[N];
int rx[N], ry[N];
double dst[N][N];

int n, r, b;

void read() {
  cin >> n >> r >> b;
  for (int i = 0 ; i < r ; i++) cin >> rx[i] >> ry[i];
  for (int i = 0 ; i < b ; i++) cin >> bx[i] >> by[i];
}

void prepare() {
  for (int i = 0 ; i < r ; i++)
    for (int j = 0 ; j < b ; j++)
      dst[i][j] = hypot(rx[i] - bx[j], ry[i] - by[j]);
}

bool vis[N];
int match[N];

int augment(int now, double lim) {
  if (vis[now]) return 0;
  vis[now] = 1;

  for (int i = 0 ; i < b ; i++)
    if (dst[now][i] < lim && (match[i] == -1 || augment(match[i], lim))) {
      match[i] = now;
      return 1;    
    }
  
  return 0;
}

int mcbm(double lim) {
  int ret = 0;
  memset(match, -1, sizeof match);

  for (int i = 0 ; i < r ; i++) {
    memset(vis, 0, sizeof vis);
    ret += augment(i, lim);
  }
  
  // cout << lim << " " << ret << endl;
  return ret;
}

int mis(double lim) {
  return r + b - mcbm(lim);
}

double work() {
  double lo = 0, hi = 1e6;

  for (int i = 0 ; i < 50 ; i++) {
    double mid = (lo + hi) / 2;

    if (mis(mid) >= n)
      lo = mid;
    else
      hi = mid;
  }

  return lo;
}

int main() {
  read();
  prepare();
  printf("%.9lf\n", work());
  return 0;
}