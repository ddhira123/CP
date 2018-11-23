#include <bits/stdc++.h>
using namespace std;

const int MX = 1e7;

long long cnt[MX + 5];
int prime[MX + 5];
int mu[MX + 5];

int a, b, c, d;

void precompute() {
  for (int i = 2; i <= MX; i++) {
    prime[i] = 1;
    mu[i] = 1;
  }
  mu[1] = 1;

  for (int i = 2; i <= MX; i++)
    if (prime[i]) {
      mu[i] = -1;

      for (int j = i + i; j <= MX; j += i) {
        mu[j] = -mu[j];
        prime[j] = 0;
      }

      if (1ll * i * i <= MX) {
        for (int j = i * i; j <= MX; j += i * i) {
          mu[j] = 0;
        }
      }
    }
}

int main() {
  precompute();
  // cin >> a >> b >> c >> d;
  // for (int i = MX ; i >= 1 ; i--) {
  //     int kiri = (b / i) - (a-1) / i;
  //     int kanan = (d / i) - (c-1) / i;

  //     cnt[i] = 1ll * kiri * kanan;
  //     for (int j = i * 2 ; j <= MX ; j += i) {
  //         cnt[i] -= cnt[j];
  //     }
  // }
  // cout << cnt[1] << endl;

  cin >> a >> b >> c >> d;
  long long ret = 0;
  for (int i = 1; i <= MX; i++) {
    int kiri = (b / i) - (a - 1) / i;
    int kanan = (d / i) - (c - 1) / i;

    // if (i <= 5)
    // printf("i %d mu %d\n", i, mu[i]);
    ret += 1ll * mu[i] * kiri * kanan;
  }
  cout << ret << endl;
  return 0;
}