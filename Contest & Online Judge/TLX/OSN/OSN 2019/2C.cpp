#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int START = 1;
const int END = -1;

struct Event {
  int time;
  int type;
  int idx;
};

int n, s, q;
vector<Event> events;
int pset[N];

int finds(int x) {
  return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

void join(int u, int v) {
  u = finds(u);
  v = finds(v);

  if (u != v) {
    pset[u] += pset[v];
    pset[v] = u;
  }
}

void init() {
  memset(pset, -1, sizeof pset);
}

void read() {
  scanf("%d %d %d", &n, &s, &q);
  for (int i = 1 ; i <= n ; i++) {
    int t; scanf("%d", &t);

    for (int j = 0 ; j < t ; j++) {
      int a, b;
      scanf("%d %d", &a, &b);

      events.push_back((Event){a, START, i});
      events.push_back((Event){b+1, END, i});
    }
  }
}

void prepare() {
  sort(events.begin(), events.end(), [](Event a, Event b) {
    if (a.time != b.time) return a.time < b.time;
    return a.type < b.type;
  });

  int activeGroup = -1;
  int cntActive = 0;

  for (auto event : events) {
    if (event.type == END) {
      cntActive--;
    } else {
      if (cntActive == 0) {
        activeGroup = finds(event.idx);
      } else {
        join(activeGroup, event.idx);
      }

      cntActive++;
    }
  }
}

void work() {
  for (int i = 0 ; i < q ; i++) {
    int idx; scanf("%d", &idx);
    printf("%d\n", -pset[finds(idx)]);
  }
}

int main() {
  init();
  read();
  prepare();
  work();
  return 0;
}
