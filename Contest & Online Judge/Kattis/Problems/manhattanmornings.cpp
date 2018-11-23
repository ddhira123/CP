#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

struct Point {
  int x;
  int y;

  void read() {
    scanf("%d %d", &x, &y);
  }
};

Point arr[N];
Point s, t;
int n;

vector<int> uniq;
int BIT[N];

void update(int x, int val) {
  for (; x < uniq.size() ; x += x & -x) {
    BIT[x] = max(BIT[x], val);
  }
}

int query(int x) {
  int ret = 0;
  while (x) {
    ret = max(ret, BIT[x]);
    x -= x & -x;
  }
  return ret;
}

int getID(int x) {
  return lower_bound(uniq.begin(), uniq.end(), x) - uniq.begin();
}

void read() {
  scanf("%d", &n);
  s.read(); t.read();

  for (int i = 0 ; i < n ; i++) {
    arr[i].read();
  }
}

void prepare() {
  if (s.x > t.x) {
    s.x = -s.x;
    t.x = -t.x;
    for (int i = 0 ; i < n ; i++) {
      arr[i].x = -arr[i].x;
    }
  }

  if (s.y > t.y) {
    s.y = -s.y;
    t.y = -t.y;
    for (int i = 0; i < n; i++) {
      arr[i].y = -arr[i].y;
    }
  }

  for (int i = 0 ; i < n ; i++) {
    uniq.push_back(arr[i].y);
  }
  uniq.push_back(t.y);
  uniq.push_back(-2e9);

  sort(uniq.begin(), uniq.end());
  uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());

  sort(arr, arr + n, [](Point a, Point b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
  });
}

int work() {
  for (int i = 0 ; i < n ; i++) {
    if (arr[i].x < s.x || arr[i].x > t.x) continue;
    if (arr[i].y < s.y || arr[i].y > t.y) continue;

    int idx = getID(arr[i].y);
    int mx = query(idx) + 1;

    update(idx, mx);
  }

  return query(getID(t.y));
}

int main() {
  read();
  prepare();
  printf("%d\n", work());
  return 0;
}