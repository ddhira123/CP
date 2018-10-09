#include <bits/stdc++.h>
using namespace std;

const int N = 4;

vector<int> adj[1 << (1 << N)];
pair<int, int> dp[16][1 << (1 << N)];
bool done[16][1 << (1 << N)];
int arr[16][16];
int n;

void precompute() {
  vector<int> masks[17];

  for (int sz = 2 ; sz <= 16 ; sz*= 2) {
    vector<int> v;
    for (int bm = 0 ; bm < (1 << sz) ; bm++)
      if (__builtin_popcount(bm) == sz / 2) {
        v.push_back(bm);
      }
    
    masks[sz] = v;
  }

  for (int i = 0 ; i < (1 << 16) ; i++) {
    vector<int> bits;
    for (int j = 0 ; j < 16 ; j++)
      if (i & (1 << j))
        bits.push_back(j);
    
    for (int x : masks[bits.size()]) {
      int ret = 0;
      for (int k = 0 ; k < 16 ; k++)
        if (x & (1 << k))
          ret += (1 << bits[k]);
      adj[i].push_back(ret);
      // printf("i %d ret %d\n", i, ret);
    }
  }

  // int ret = 0;
  // for (int i = 0 ; i < (1 << 16) ; i++)
  //   ret += adj[i].size();
  // cout << ret << endl;
}

pair<int, int> combat(pair<int, int> a, pair<int, int> b) {
  int i = a.first;
  int j = b.first;

  if (arr[i][j] > 0) {
    return {i, a.second + arr[i][j]};
  }

  return {j, b.second + arr[j][i]};
}

pair<int, int> solve(int won, int mask) {
  if(__builtin_popcount(mask) == 1) {
    if (mask == (1 << won)) return {won, 0};
    return {-1, -1};
  }

  if (done[won][mask]) return dp[won][mask];
  done[won][mask] = 1;

  pair<int, int> ret = {-1, -1};
  for (int nex : adj[mask]) {
    if (nex & (1 << won)) continue;
    pair<int, int> kiri = solve(won, mask - nex);

    for (int i = 0 ; i < (1 << n) ; i++)
      if (((1 << i) & nex) != 0) {
        pair<int, int> kanan = solve(i, nex);
        if (kiri.first == -1 || kanan.first == -1) continue;

        pair<int, int> val = combat(kiri, kanan);
        if (val.first != won) continue;

        if (ret.first == -1) ret = val;
        else {
          ret.second = min(ret.second, val.second);
        }
      }
  }

  return dp[won][mask] = ret;
}

int main() {
  precompute();
  scanf("%d", &n);
  for (int i = 0 ; i < (1 << n) ; i++)
    for (int j = 0 ; j < (1 << n) ; j++)
      scanf("%d", &arr[i][j]);
  // n = 4;
  // for (int i = 0 ; i < (1 << n) ; i++) {
  //   for (int j = i+1 ; j < (1 << n) ; j++) {
  //     int rnd = rand() % 2;
  //     if (rnd == 0) {
  //       arr[i][j] = rand() % 100;
  //       arr[j][i] = -1;
  //     } else {
  //       arr[i][j] = -1;
  //       arr[j][i] = rand() % 100;
  //     }
  //   }
  // }
  
  pair<int, int> ret = solve(0, (1 << (1 << n)) - 1);
  // printf("ret %d %d\n", ret.first, ret.second);
  if (ret.first == 0) printf("%d\n", ret.second);
  else printf("-1\n");
  return 0;
}