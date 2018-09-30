#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

long long BIT[N];

string s;
int n, q;
int leftLimit[N];

void update(int x, int val) {
  for (; x <= n; x += x & -x) BIT[x] += val;
}

long long query(int x) {
  long long ret = 0;
  while (x) {
    ret += BIT[x];
    x -= x & -x;
  }
  return ret;
}

void read() { cin >> n >> q >> s; }

void changeLimit(int l, int r) {
  int i = l - 1;
  int mask = 0;

  while (i >= 0 && (mask & (1 << (s[i] - 'a'))) == 0) {
    mask |= 1 << (s[i] - 'a');
    i--;
  }

  update(l, -leftLimit[l]);
  leftLimit[l] = i + 1;
  update(l, leftLimit[l]);

  for (int j = l + 1; j <= r; j++) {
    while ((mask & (1 << (s[j - 1] - 'a'))) != 0) {
      i++;
      mask ^= (1 << (s[i] - 'a'));
    }

    update(j, -leftLimit[j]);
    leftLimit[j] = i + 1;
    update(j, leftLimit[j]);

    mask |= (1 << (s[j - 1] - 'a'));
  }
}

long long answer(int l, int r) {
  long long ret = 1ll * (r - l + 1) * (l + r) / 2;
  ret -= (query(r) - query(l - 1));

  for (int i = l; i <= r; i++) {
    if (leftLimit[i] >= l) {
      break;
    } else {
      ret += leftLimit[i];
      ret -= (l - 1);
    }
  }

  return ret;
}

void prepare() { changeLimit(1, n); }

void work() {
  for (int i = 0; i < q; i++) {
    int opt;
    scanf("%d", &opt);

    if (opt == 1) {
      int pos;
      char ch[5];

      scanf("%d %s", &pos, ch);
      s[pos - 1] = ch[0];

      changeLimit(pos, min(n, pos + 26));
    } else {
      int l, r;
      scanf("%d %d", &l, &r);

      printf("%lld\n", answer(l, r));
    }
  }
}

int main() {
  read();
  prepare();
  work();
  return 0;
}