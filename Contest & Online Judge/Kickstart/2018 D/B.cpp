#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int K = 1e5 + 5;

pair<int, int> tower[N];
pair<int, int> balloon[N];
bool flag[N];
int n, k;

int x[4], y[4], a[4], b[4], c[4], m[4];

void read() {
  scanf("%d %d", &n, &k);
  for(int i = 0 ; i < 4 ; i++) {
    scanf("%d %d %d %d %d %d", x + i, y + i, a + i, b + i, c + i, m + i);
  }
}

void prepare() {
  tower[1].first = x[0], tower[2].first = y[0];
  for(int i = 3 ; i <= n ; i++) {
    tower[i].first = (1ll * a[0] * tower[i-1].first + 1ll * b[0] * tower[i-2].first + c[0]) % m[0] + 1;
  }

  tower[1].second = x[1], tower[2].second = y[1];
  for(int i = 3 ; i <= n ; i++) {
    tower[i].second = (1ll * a[1] * tower[i-1].second + 1ll * b[1] * tower[i-2].second + c[1]) % m[1] + 1;
  }

  balloon[1].first = x[2], balloon[2].first = y[2];
  for(int i = 3 ; i <= k ; i++) {
    balloon[i].first = (1ll * a[2] * balloon[i-1].first + 1ll * b[2] * balloon[i-2].first + c[2]) % m[2] + 1;
  }

  balloon[1].second = x[3], balloon[2].second = y[3];
  for(int i = 3 ; i <= k ; i++) {
    balloon[i].second = (1ll * a[3] * balloon[i-1].second + 1ll * b[3] * balloon[i-2].second + c[3]) % m[3] + 1;
  }

  // for(int i = 1 ; i <= n ; i++) printf("%d %d\n", tower[i].first ,tower[i].second);
  // puts("===");
  // for(int i = 1 ; i <= k ; i++) printf("%d %d\n", balloon[i].first ,balloon[i].second);


  sort(tower + 1, tower + n + 1);
  sort(balloon + 1, balloon + k + 1);
  memset(flag, 0, sizeof flag);
}

int work() {
  int mx = -2e9 - 1;
  for(int i = 1, j = 0 ; i <= k ; i++) {
    while(j+1 <= n && tower[j+1].first <= balloon[i].first) {
      mx = max(mx, tower[j+1].first + tower[j+1].second);
      j++;
    }

    if(mx >= balloon[i].first + balloon[i].second)
      flag[i] = 1;
  }

  mx = -2e9 - 1;
  for(int i = k, j = n+1 ; i >= 1 ; i--) {
    while(j-1 >= 1 && tower[j-1].first >= balloon[i].first) {
      mx = max(mx, tower[j-1].second - tower[j-1].first);
      j--;
    }

    if(mx >= balloon[i].second - balloon[i].first)
      flag[i] = 1;
  }
  return accumulate(flag, flag + k + 1, 0);
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    cerr << "now " << tc << endl;
    read();
    prepare();

    printf("Case #%d: %d\n", tc, work());
  }
  return 0;
}