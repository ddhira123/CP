#include <bits/stdc++.h>
using namespace std;

const int BUCKET = 500;
const int MAGIC = 32;
const int N = 200005;

int bucket[N / BUCKET + 5][2][MAGIC];
int add[N / BUCKET + 5];
int arr[N];
int n, m, q;

int magic;

void read() {
  cin >> n >> m >> q;
  for (int i = 0 ; i < n ; i++) {
    long long x; scanf("%lld", &x);
    arr[i] = x % 2;
  }
  magic = (1 << m);
}

int getBucket(int x) { return x / BUCKET; }

int getLeft(int x) {
  return x * BUCKET;
}

int getRight(int x) {
  return min(n-1, (x + 1) * BUCKET - 1);
}

int operate(int idx, int mask, bool flipped) {
  int tmp = mask;

  int zero = 1;
  if (mask == magic-1) zero = 0;

  mask <<= 1;
  mask &= (magic-1);
  mask |= (arr[idx] ^ flipped ? zero : 1);

  // printf("oper %d %d %d -> %d\n", idx, tmp, flipped, mask);
  return mask;
}

void makeBucket(int idx) {
  int l = getLeft(idx);
  int r = getRight(idx);

  for (int flipped = 0 ; flipped < 2 ; flipped++) {
    for (int msk = magic-1 ; msk >= 0 ; msk--) {
      int cur = msk;

      for (int i = r ; i >= l ; i--) {
        cur = operate(i, cur, flipped);
      }

      bucket[idx][flipped][msk] = cur;
    }
  }
}

// r-l+1 <= m
int naive(int l, int r) {
  int mask = (arr[r] ^ add[getBucket(r)] ? 0 : 1);

  for (int i = r-1 ; i >= l ; i--) {
    // printf("n %d %d %d\n", l, r, i);
    int zero = 1;
    if (mask == (1 << (r-i))-1) zero = 0;

    mask <<= 1;
    mask &= (magic - 1);
    mask |= (arr[i] ^ add[getBucket(i)] ? zero : 1);
  }

  return mask;
}

int solve(int l, int r) {
  if (r - l + 1 <= m) return naive(l, r) & 1;
  int cur = naive(r-m+1, r);

  r = r - m;
  if (r < l) return cur & 1;

  int ll = getBucket(l);
  int rr = getBucket(r);

  if (ll == rr) {
    for (int i = r ; i >= l ; i--) {
      cur = operate(i, cur, add[ll]);
    }
    return cur & 1;
  }

  for (int i = r ; i >= getLeft(rr) ; i--) {
    cur = operate(i, cur, add[rr]);
  }

  for (int i = rr-1 ; i > ll ; i--) {
    cur = bucket[i][add[i]][cur];
    // printf("now i %d cur %d\n", i, cur);
  }

  // printf("ll %d\n", ll);

  for (int i = getRight(ll) ; i >= l ; i--) {
    cur = operate(i, cur, add[ll]);
  }

  // cout << cur << endl;
  return cur & 1;
}

void update(int l, int r, long long x) {
  x %= 2;
  if (x == 0) return;

  int ll = getBucket(l);
  int rr = getBucket(r);

  if (ll == rr) {
    for (int i = l ; i <= r ; i++) {
      arr[i] ^= 1;
    }

    makeBucket(ll);
    return;
  }

  for (int i = l ; i <= getRight(ll) ; i++) {
    arr[i] ^= 1;
  }
  makeBucket(ll);
  for (int i = ll+1 ; i < rr ; i++) {
    add[i] ^= 1;
  }
  for (int i = getLeft(rr) ; i <= r ; i++) {
    arr[i] ^= 1;
  }
  makeBucket(rr);
}

int main() {
  read();

  for (int i = 0 ; i <= getBucket(n-1) ; i++) {
    makeBucket(i);
  }

  for (int i = 0 ; i < q ; i++) {
    int opt, l, r; 
    scanf("%d %d %d", &opt, &l, &r);

    l--; r--;
    if (opt == 2) {
      int ret = solve(l, r);
      printf("%d\n", ret ? 1 : 2);
    } else {
      long long x; scanf("%lld", &x);
      update(l, r, x);
    }
  }
  return 0;
}