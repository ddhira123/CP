#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int MX = 30;
const int LOG = 20;

int st[LOG][N];
int pwr2[N];
int arr[N];
int n, k;

pair<int, int> dp[N];

int get(int l, int r) {
  if (l > r) return 0;
  
  int ret = 0;
  int pwr = pwr2[r - l + 1];
  ret = st[pwr][l] | st[pwr][r - (1 << pwr) + 1];
  return ret;
}

bool test(int mask) {
  for (int i = 1, l = 1 ; i <= n ; i++) {
    while (l+1 <= i && (get(l+1, i) & mask) == mask) l++;

    if ((get(l, i) & mask) == mask) {
      dp[i] = dp[l-1];
      dp[i].first++;
    } else {
      dp[i].first = 0;
      dp[i].second = get(l, i) & mask;
    }
  }

  for (int i = 1 ; i <= n ; i++) {
    pair<int, int> cur = dp[i];
    int sisa = get(i+1, n);
    int res = cur.first;

    if (((sisa | cur.second) & mask) == mask) {
      res++;
    }

    if (res >= k) return 1;
  }

  return 0;
}

int main() {
  scanf("%d %d", &n, &k);
  // n = 1000000;
  // k = rand() % n + 1;
  for (int i = 1 ; i <= n ; i++) {
    scanf("%d", &arr[i]);
    st[0][i] = arr[i];
    // arr[i] = rand() % 1000000001;
  }

  for (int lg = 1 ; (1 << lg) <= n ; lg++)
    for (int i = 1 ; i + (1 << lg) - 1 <= n ; i++)
      st[lg][i] = st[lg-1][i] | st[lg-1][i + (1 << (lg-1))];
  for (int i = 2 ; i <= n ; i++) {
    pwr2[i] = pwr2[i-1];
    if ((1 << (pwr2[i]+1)) == i) pwr2[i]++;
  }


  int ret = 0;
  for (int i = MX - 1 ; i >= 0 ; i--)
    if (test(ret | (1 << i))) {
      ret |= (1 << i);
    }
  
  printf("%d\n", ret);
  return 0;
}