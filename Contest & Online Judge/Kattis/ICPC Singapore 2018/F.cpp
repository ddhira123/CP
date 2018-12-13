#include <bits/stdc++.h>
using namespace std;

struct Node {
  pair<int, int> a;
  pair<int, int> b;

  Node() {
    a = b = {-1, -1};
  }

  void update(int idx, int x) {
    a.first = idx;
    a.second = x;
  }

  Node operator +(Node other) const {
    vector<pair<int, int>> v = {a, b, other.a, other.b};
    sort(v.begin(), v.end(), [](pair<int, int> x, pair<int, int> y) {
      return x.second > y.second;
    });

    Node res;
    res.a = v[0];
    res.b = v[1];

    return res;
  }

  int extract(int x) {
    if (x == a.first) return b.second;
    return a.second;
  }
};

const int N = 4e5 + 5;

Node stree[4 * N];
int lst[N];
int prv[N];
int nex[N];
int arr[N];
int start[N];
int n;

void update(int id, int l, int r, int x, int val) {
  if (l == r) {
    stree[id].update(x, val);
  } else {
    int m = (l + r) / 2;
    int chld = id << 1;

    if (x <= m) update(chld, l, m, x, val);
    else        update(chld+1, m+1, r, x, val);

    stree[id] = stree[chld] + stree[chld+1];
  }
}

Node query(int id, int l, int r, int x, int y) {
  if (x <= l && r <= y) {
    return stree[id];
  } else {
    int m = (l + r) / 2;
    int chld = id << 1;

    Node res;
    if (x <= m) res = res + query(chld, l, m, x, y);
    if (y > m)  res = res + query(chld+1, m+1, r, x, y);

    return res;
  }
}

int query2(int id, int l, int r, int x, int tgt) {
  if (stree[id].extract(x) <= tgt) return -1;
  if (l == r) return l;

  int m = (l + r) / 2;
  int chld = id << 1;

  int kiri = query2(chld, l, m, x, tgt);
  if (kiri != -1) return kiri;

  return query2(chld+1, m+1, r, x, tgt);
}

void read() {
  memset(nex, -1, sizeof nex);

  scanf("%d", &n);
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &arr[i]);
    prv[i] = lst[arr[i]];
    nex[prv[i]] = i;
    lst[arr[i]] = i;

    if (start[arr[i]] == 0) {
      start[arr[i]] = i;
    }
  }

  for (int i = 1 ; i <= n ; i++)
    if (nex[i] == -1)
      nex[i] = n+1;
}

int test(int idx) {
  int val = arr[idx];
  return query2(1, 1, n, val, start[val]);
  // Node all = query(1, 1, n, 1, n);

  // if (all.extract(val) <= start[val]) return -1;
  
  // int lo = 1, hi = n;
  // while (lo < hi) {
  //   int mid = (lo + hi) / 2;
  //   Node cur = query(1, 1, n, 1, mid);

  //   if (cur.extract(val) > start[val]) {
  //     hi = mid;
  //   } else {
  //     lo = mid+1;
  //   }
  // }
  
  // return lo;
}

void work() {
  vector<int> order(n+1);
  iota(order.begin()+1, order.end(), 1);
  sort(order.begin(), order.end(), [&](int a, int b) {
    return prv[a] < prv[b];
  });

  int it = 1;
  pair<int, int> res = {-1, -1};

  for (int i = 1 ; i <= n ; i++) {
    while (it <= n && prv[order[it]] < i) {
      int idx = order[it];
      update(1, 1, n, arr[idx], prv[idx]);
      it++;
    }

    int val = test(i);
    pair<int, int> cur = {arr[i], val};
    if (val != -1 && (res.first == -1 || cur < res)) {
      res = cur;
    }

    if (nex[i] == n+1) {
      // printf()
      update(1, 1, n, arr[i], -1);
    }
  }

  if (res.first == -1) puts("-1");
  else printf("%d %d\n", res.first, res.second);
}

int main() {
  read();
  work();
  return 0;
}