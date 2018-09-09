#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

map<string, int> mapping;

int pset[N];

int get_idx(string name) {
  if(mapping.count(name)) {
    return mapping[name];
  }

  return mapping[name] = mapping.size();
}

int finds(int x) {
  return pset[x] < 0 ? x : pset[x] = finds(pset[x]);
}

void join(int x, int y) {
  x = finds(x);
  y = finds(y);

  if(x != y) {
    pset[x] += pset[y];
    pset[y] = x;
  }
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    memset(pset, -1, sizeof pset);
    mapping.clear();
    
    int n; cin >> n;

    for(int i = 0 ; i < n ; i++) {
      string a, b;
      cin >> a >> b;

      int a_idx = get_idx(a);
      int b_idx = get_idx(b);

      join(a_idx, b_idx);
      printf("%d\n", -pset[finds(a_idx)]);
    }
  }
  return 0;
}