// in the middle of coding but decided to stop, WA in contest
#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

struct Fenwick {
  long long bit[N];
  int n;

  Fenwick() {
    memset(bit, 0, sizeof bit);
  }

  void update(int x, int val) {
    for(; x < N ; x += x & -x)
      bit[x] += val;
  }

  long long query(int x) {
    long long ret = 0;
    while (x) {
      ret += bit[x];
      x -= x & -x;
    }
    return ret;
  }

  long long query(int x, int y) {
    return query(y) - query(max(0, x-1));
  }
};

int n, k;
int arr[N];

Fenwick cnt[2], sums[2];
vector<int> uniq;

int batasKiri[N], batasKanan[N];

int getIdx(int x) {
  return lower_bound(uniq.begin(), uniq.end(), x) - uniq.begin();
}

void read() {
  scanf("%d %d", &n, &k);
  for(int i = 1 ; i <= n ; i++) {
    scanf("%d", &arr[i]);
  }
}

void prepare() {
  uniq.push_back(-1e9);
  for(int i = 1 ; i <= n ; i++)
    uniq.push_back(arr[i]);
  sort(uniq.begin(), uniq.end());

  for(int i = 1 ; i <= n ; i++) {
    int lo = max(1, i - k + 1), hi = i;
    while (lo < hi) {
      int mid = (lo + hi) / 2;
      if ()
    }
  }
}

long long work() {
  long long ret = 0;

  int l[2], r[2];

  for (int i = 1 ; i <= n ; i++) {
    int prv = i - (k - 1);
    int parity = prv % 2 == 0 ? 0 : 1;

    if (prv >= 3) {
      int pos = prv - 2;
      int idx = getIdx(arr[pos]);

      cnt[parity].update(idx, -1);
      sums[parity].update(idx, -arr[pos]);
    }

    int idx = getIdx(arr[i]);
    cnt[i % 2].update(idx, 1);
    sums[i % 2].update(idx, arr[i]);

    if (i < (k+1) / 2 + 1) continue;

    if (i > n - k + 1) {
      int toRight = n - i;
      int fromLeft = n - k + 1 + toRight;

      if (fromLeft + 2 <= i) {
        int pos = fromLeft + 2;
        int idx = getIdx(arr[pos]);

        cnt[parity].update(idx, -1);
        sums[parity].update(idx, -arr[pos]);
      }
    }
    
    int cntLow = cnt[parity].query(0, idx);
    long long sumLow = sums[parity].query(0, idx);
    int cntHigh = cnt[parity].query(idx+1, N-1);
    long long sumHigh = sums[parity].query(idx+1, N-1);

    ret += (1ll * cntLow * arr[i] - sumLow);
    ret += (sumHigh - 1ll * cntHigh * arr[i]);
  }

  return ret;
}

int main() {
  read();
  prepare();
  printf("%lld\n", work());
  return 0;
}