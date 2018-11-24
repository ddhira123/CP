#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int K = 15;

int arr[K][N];
int pos[K][N];
// set<pair<int, int>> st[K];

int n, k;

void read() {
  scanf("%d %d", &n, &k);

  for(int i = 0 ; i < k ; i++) {
    for (int j = 1 ; j <= n ; j++) {
      scanf("%d", &arr[i][j]);
    }
  }
}

void prepare() {
  for (int i = 0 ; i < k ; i++)
    for (int j = 1 ; j <= n ; j++)
      pos[i][arr[i][j]] = j;
}

long long work() {
  long long ans = 0;
  int cur = 0;
  
  for (int i = 1 ; i <= n ; i++) {
    int prv = arr[0][i-1];
    int now = arr[0][i];

    for (int j = 0 ; j < k ; j++) {
      int post = pos[j][prv];
      if (arr[j][post+1] != now)
        cur = 0;
    }

    cur++;
    ans += cur;
  }

  return ans;
}

int main() {
  read();
  prepare();
  printf("%lld\n", work());
  return 0;
}