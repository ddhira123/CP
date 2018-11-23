#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int MAGIC = 100;

pair<int, long double> arr[N];
int n;

void read() {
  scanf("%d", &n);
  for (int i = 0 ; i < n ; i++) {
    scanf("%d %Lf", &arr[i].first, &arr[i].second);
  }
}

// precision error
bool check(long double L) {
  long double mx1 = -4e18;
  long double mx2 = -4e18;

  for (int i = 0 ; i < n ; i++) {
    int y = arr[i].first;
    long double fy = arr[i].second;

    if (mx1 - fy - L * y > 1e-9) return 0;
    if (mx2 + fy - L * y > 1e-9) return 0;

    mx1 = max(mx1, fy + L * y);
    mx2 = max(mx2, -fy + L * y);
  }

  return 1;
}

long double work() {
  sort(arr, arr + n);
  long double mx = 0;

  for (int i = 0 ; i+1 < n ; i++) {
    mx = max(mx, fabs(arr[i].second - arr[i+1].second) / (arr[i+1].first - arr[i].first));
  }

  return mx;
}

int main() {
  read();
  printf("%.12Lf\n", work());
  return 0;
}