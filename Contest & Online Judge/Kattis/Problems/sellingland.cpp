#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

char s[N][N];
int n, m;

int height[N];
int ans[4 * N];

void read() {
  scanf("%d %d", &n, &m);
  for (int i = 0 ; i < n ; i++) {
    scanf("%s", s[i]);
  }
}

void work() {
  memset(height, 0, sizeof height);
  memset(ans, 0, sizeof ans);

  for (int i = 0 ; i < n ; i++) {
    // <kiri, height>
    vector<pair<int, int>> stek;
    // <val, kiri>
    set<pair<int, int>> st;

    for (int j = 0 ; j < m ; j++) {
      if (s[i][j] == '#') {
        stek.clear();
        st.clear();
        height[j] = 0;
        continue;
      }

      height[j]++;

      int kiri = j;
      while (!stek.empty() && stek.back().second >= height[j]) {
        int val = stek.back().second - stek.back().first + 1;
        st.erase({val, stek.back().first});

        kiri = stek.back().first;
        stek.pop_back();
      }

      stek.push_back({kiri, height[j]});
      st.insert({height[j] - kiri + 1, kiri});

      int mx = (*st.rbegin()).first + j;
      mx *= 2;
      ans[mx]++;
    }
  }

  for (int i = 0 ; i < 4*N ; i++)
    if (ans[i]) {
      printf("%d x %d\n", ans[i], i);
    }
}

int main() {
  int t; cin >> t;
  for (int tc = 1 ; tc <= t ; tc++) {
    read();
    work();
  }
  return 0;
}