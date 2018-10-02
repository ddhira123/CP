#include <bits/stdc++.h>
using namespace std;

const int MX = 1e5 + 5;

struct Node {
  int mins;
  int mins_cnt;
  int lazy;

  void add_lazy(int x) {
    lazy += x;
    mins += x;
  }

  Node operator +(Node other) const {
    Node ret;
    ret.lazy = 0;

    if (mins < other.mins) {
      ret.mins = mins; 
      ret.mins_cnt = mins_cnt;
    } else if(other.mins < mins) {
      ret.mins = other.mins;
      ret.mins_cnt = other.mins_cnt;
    } else {
      ret.mins = mins;
      ret.mins_cnt = mins_cnt + other.mins_cnt;
    }

    return ret;
  }
};

int prime[MX];
set<int> idxs[MX];
Node stree[4 * MX];
int arr[MX];
int n, k, m;

void precompute() {
  for (int i = 2 ; i < MX ; i++)
    if (prime[i] == 0) {
      for (int j = i ; j < MX ; j += i)
        prime[j] = i;
    }
}

void build(int id, int l, int r) {
  if (l == r) {
    stree[id] = (Node){0, 1, 0};
  } else {
    int m = (l + r) / 2;
    int chld = id << 1;

    build(chld, l, m);
    build(chld+1, m+1, r);

    stree[id] = stree[chld] + stree[chld+1];
  }
}

void propagate(int id) {
  int chld = id << 1;

  for (int i = 0 ; i < 2 ; i++) {
    stree[chld + i].lazy += stree[id].lazy;
    stree[chld + i].mins += stree[id].lazy;
  }

  stree[id].lazy = 0;
}

void update(int id, int l, int r, int x, int y, int val) {
  if (x <= l && r <= y) {
    stree[id].lazy += val;
    stree[id].mins += val;
  } else {
    int m = (l + r) / 2;
    int chld = id << 1;

    propagate(id);
    if (x <= m) update(chld, l, m, x, y, val);
    if (y > m)  update(chld+1, m+1, r, x, y, val);

    stree[id] = stree[chld] + stree[chld+1];
  }
}

void debug(int id, int l, int r) {
  if (l == r) {
    printf("l %d -> %d %d\n", l, stree[id].mins, stree[id].mins_cnt);
  } else {
    int m = (l + r) / 2;
    int chld = id << 1;

    propagate(id);
    debug(chld, l, m);
    debug(chld+1, m+1, r);

    stree[id] = stree[chld] + stree[chld+1];
  }
}

void updater(int l, int r, int val) {
  if (r - l + 1 > k) return;

  int kiri = max(1, r - k + 1);
  int kanan = min(l, n - k + 1);

  update(1, 1, n-k+1, kiri, kanan, val);
}

void adder(int pos, int val) {
  while (val != 1) {
    int p = prime[val];
    while (val % p == 0) val /= p;
    idxs[p].insert(pos);

    {
      auto it = idxs[p].upper_bound(pos);
      auto it2 = idxs[p].lower_bound(pos);

      if (it != idxs[p].end() && it2 != idxs[p].begin()) {
        it2--;

        int l = *it2;
        int r = *it;
        updater(l, r, -1);
      }
    }

    // printf("add pos %d prime %d\n", pos, p);

    auto it = idxs[p].upper_bound(pos);
    if (it != idxs[p].end()) {
      int idx = *it;

      updater(pos, idx, 1);
    }

    it = idxs[p].lower_bound(pos);
    if (it != idxs[p].begin()) {
      it--;

      int idx = *it;
      updater(idx, pos, 1);
    }
  }

  // printf("now %d -> %d\n", stree[1].mins, stree[1].mins_cnt);
}

void remover(int pos, int val) {
  while (val != 1) {
    int p = prime[val];
    while (val % p == 0) val /= p;

    // printf("rem pos %d prime %d\n", pos, p);
    {
      auto it = idxs[p].upper_bound(pos);
      auto it2 = idxs[p].lower_bound(pos);

      if (it != idxs[p].end() && it2 != idxs[p].begin()) {
        it2--;

        int l = *it2;
        int r = *it;
        updater(l, r, 1);
      }
    }

    auto it = idxs[p].upper_bound(pos);
    if (it != idxs[p].end()) {
      int idx = *it;

      updater(pos, idx, -1);
    }

    it = idxs[p].lower_bound(pos);
    if (it != idxs[p].begin()) {
      it--;

      int idx = *it;
      updater(idx, pos, -1);
    }

    idxs[p].erase(pos);
  }

  // printf("now %d -> %d\n", stree[1].mins, stree[1].mins_cnt);
}

void change_val(int pos, int val) {
  remover(pos, arr[pos]);
  arr[pos] = val;
  adder(pos, arr[pos]);
}

int main() {
  precompute();
  scanf("%d %d %d", &n, &k, &m);
  build(1, 1, n-k+1);

  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &arr[i]);
    adder(i, arr[i]);
  }

  printf("%d\n", n-k+1 - (stree[1].mins == 0 ? stree[1].mins_cnt : 0));

  for (int i = 0 ; i < m ; i++) {
    int pos, val;
    scanf("%d %d", &pos, &val);
    change_val(pos, val);
    // debug(1, 1, n-k+1);

    printf("%d\n", n-k+1 - (stree[1].mins == 0 ? stree[1].mins_cnt : 0));
  }

  printf("%lld\n", accumulate(arr + 1, arr + n + 1, 0ll));
  return 0;
}