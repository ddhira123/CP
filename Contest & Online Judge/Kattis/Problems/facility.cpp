#include <bits/stdc++.h>
using namespace std;

const int N = 105;

bool covered[N];
int m, n, k;

int main() {
  scanf("%d %d %d", &m, &n, &k);
  int ret = 0;
  int client = 0;

  for(int i = 0 ; i < m ; i++) {
    int use = 0;

    for(int j = 0 ; j < n ; j++) {
      int x; scanf("%d", &x);

      if(!covered[j] && x == 0) {
        covered[j] = 1;
        use = 1;
        client++;
      }
    }

    ret += use;
  }

  printf("%s\n", (ret <= k && client == n) ? "yes" : "no");
  return 0;
}