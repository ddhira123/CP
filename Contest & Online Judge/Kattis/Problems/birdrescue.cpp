#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
const int MAX_VAL = 2e6 + 5;

struct Rectangle {
  int x1, y1;
  int x2, y2;

  void read() {
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    if(x1 > x2) swap(x1, x2);
    if(y1 > y2) swap(y1, y2);
  }

  pair<int, int> get_dist(int x, int y) {
    int mins = 0;
    
    if(x < x1) mins += (x1 - x);
    else if(x > x2) mins += (x - x2);

    if(y < y1) mins += (y1 - y);
    else if(y > y2) mins += (y - y2);

    int maks = 0;
    maks += max(abs(x1 - x), abs(x2 - x));
    maks += max(abs(y1 - y), abs(y2 - y));

    pair<int, int> ret = {mins, maks};
    return ret;
  }
};

int BIT[MAX_VAL];

void update(int x, int val) {
  x++;
  for(; x < MAX_VAL ; x += x & -x) {
    BIT[x] += val;
  }
}

int query(int x) {
  x++;
  int ret = 0;
  while(x) {
    ret += BIT[x];
    x -= x & -x;
  }
  return ret;
}

Rectangle person[N];
int n, q;
int xa, ya;
vector<pair<int, int>> dist;
pair<int, int> queries[N];
int ans[N];

void read() {
  scanf("%d %d", &n, &q);
  scanf("%d %d", &xa, &ya);

  for(int i = 0 ; i < n ; i++) {
    person[i].read();
  }
  for(int i = 0 ; i < q ; i++) {
    queries[i].second = i;
    scanf("%d", &queries[i].first);
  }
}

void prepare() {
  for(int i = 0 ; i < n ; i++) {
    dist.push_back(person[i].get_dist(xa, ya));
  }

  sort(dist.begin(), dist.end(), [](pair<int, int> a, pair<int, int> b){
    return a.second < b.second;
  });
  sort(queries, queries + q);

  for(int i = 0 ; i < n ; i++) {
    update(dist[i].first, 1);
  }
}

void work() {
  int it = 0;
  for(int i = 0 ; i < q ; i++) {
    int x = queries[i].first;
    int idx = queries[i].second;

    while(it < n && x > dist[it].second) {
      update(dist[it].first, -1);
      it++;
    }

    ans[idx] = query(x);
  }

  for(int i = 0 ; i < q ; i++) {
    printf("%d\n", ans[i]);
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}