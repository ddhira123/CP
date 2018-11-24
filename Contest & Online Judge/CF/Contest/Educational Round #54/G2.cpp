#include <bits/stdc++.h>
using namespace std;

const int MAGIC = 32;
const int N = 200005;

int n, m, q;

struct Node {
  int tag;
  int val[2][MAGIC];

  void init(int curVal) {
    tag = 0;

    for (int flipped = 0 ; flipped < 2 ; flipped++)
      for (int bm = 0 ; bm < (1 << m) ; bm++) {
        int mask = bm;
        int zero = 1;
        if (mask == (1<<m) - 1) zero = 0;

        mask <<= 1;
        mask &= ((1 << m) - 1);
        mask |= (curVal ^ flipped ? zero : 1);

        val[flipped][bm] = mask;

        // printf("%d %d -> %d\n", flipped, bm, mask);
      }
  }

  Node operator +(Node other) const {
    Node res;
    res.tag = 0;

    for (int flipped = 0 ; flipped < 2 ; flipped++) {
      for (int i = 0 ; i < (1 << m) ; i++) {
        int kanan = other.eval(flipped, i);
        int kiri = eval(flipped, kanan);

        res.val[flipped][i] = kiri;
      }
    }

    return res;
  }

  int eval(int flip, int x) const {
    return val[flip ^ tag][x];
  }
};

int arr[N];
Node stree[4 * N];

void propagate(int id) {
  int chld = id << 1;

  stree[chld].tag ^= stree[id].tag;
  stree[chld + 1].tag ^= stree[id].tag;

  stree[id].tag = 0;
}

void build(int id, int l, int r) {
  if (l == r) {
    stree[id].init(arr[l]);
  } else {
    int chld = id << 1;
    int mid = (l + r) / 2;

    build(chld, l, mid);
    build(chld+1, mid+1, r);

    stree[id] = stree[chld] + stree[chld + 1];
  }
}

void update(int id, int l, int r, int x, int y) {
  if (x <= l && r <= y) {
    stree[id].tag ^= 1;
  } else {
    int chld = id << 1;
    int mid = (l + r) / 2;
    propagate(id);

    if (x <= mid) update(chld, l, mid, x, y);
    if (y > mid)  update(chld+1, mid+1, r, x, y);

    stree[id] = stree[chld] + stree[chld+1];
  }
}

int query(int id, int l, int r, int x, int y, int v) {
  if (x <= l && r <= y) {
    // printf("di %d %d %d dari %d jadi %d\n", id, l, r, v, stree[id].eval(v));
    return stree[id].eval(0, v);
  } else {
    int chld = id << 1;
    int mid = (l + r) / 2;
    propagate(id);

    if (y > mid)  v = query(chld+1, mid+1, r, x, y, v);
    if (x <= mid) v = query(chld, l, mid, x, y, v);

    stree[id] = stree[chld] + stree[chld+1];
    return v;
  }
}

void read() {
  cin >> n >> m >> q;
  for (int i = 1 ; i <= n ; i++) {
    long long x; scanf("%lld", &x);
    arr[i] = x % 2;
  }
}

int main() {
  read();
  build(1, 1, n);

  // for (int i = 1 ; i <= n ; i++) {
  //   printf("i %d -> %d\n", i, query(1, 1, n, i, i, (1 << m) - 1));
  // }

  for (int i = 1 ; i <= q ; i++) {
    int opt, l, r; 
    scanf("%d %d %d", &opt, &l, &r);

    if (opt == 2) {
      int ret = query(1, 1, n, l, r, (1 << m)-1);
      ret &= 1;
      printf("%d\n", ret ? 1 : 2);
    } else {
      long long x; scanf("%lld", &x);
      if (x % 2 == 1)
        update(1, 1, n, l, r);
    }
  }
  return 0;
}