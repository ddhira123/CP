#include <bits/stdc++.h>
using namespace std;

vector<pair<double, double>> v;
int n;

void read() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    double a, s;
    scanf("%lf %lf", &a, &s);

    v.push_back({a, s});
  }
}

double solve(vector<pair<double, double>> arr) {
  double ret = 0;
  double v = 0;

  for (auto it : arr) {
    ret += v * it.second + it.first * it.second * it.second / 2;
    v += it.first * it.second;
  }

  return ret;
}

int main() {
  read();
  double st = solve(v);

  sort(v.begin(), v.end());
  reverse(v.begin(), v.end());

  double en = solve(v);
  printf("%.1lf\n", en - st);
  return 0;
}