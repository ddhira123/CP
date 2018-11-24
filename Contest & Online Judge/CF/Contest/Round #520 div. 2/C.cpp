#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int n, q;
string s;

int pwr[N];
int psum[N];

void precompute() {
  pwr[0] = 1;
  for (int i = 1 ; i < N ; i++) {
    pwr[i] = 2 * pwr[i-1] % MOD;
  }
}

void read() {
  cin >> n >> q >> s;
}

void work() {
  for (int i = 1 ; i <= n ; i++) {
    psum[i] = psum[i-1] + (s[i-1] - '0');
  }

  for (int i = 0 ; i < q ; i++) {
    int l, r;
    scanf("%d %d", &l, &r);

    int ones = psum[r] - psum[l-1];
    int zero = r-l+1 - ones;

    int ret = 0;
    if (ones > 0) {
      ret = pwr[ones]-1;
      ret = (ret + 1ll * (pwr[ones]-1) * (pwr[zero]-1)) % MOD;
    }

    printf("%d\n", ret);
  }
}

int main() {
  precompute();
  read();
  work();
  return 0;
}