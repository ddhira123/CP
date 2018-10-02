#include <bits/stdc++.h>
using namespace std;

const string X = "ICPCASIASG";

bool vis[11][105][105];
string s;
int n;

int getIndex(int r, int c) {
  return r * n + c;
}

void dfs(int idx, int r, int c) {
  if (idx == X.length()-1) {
    cout << "YES" << endl;
    exit(0);
  }
  if (vis[idx][r][c]) return;

  for(int i = -2 ; i <= 2 ; i++)
    for (int j = -2 ; j <= 2 ; j++) {
      int nr = r + i, nc = c + j;

      if (nr >= 0 && nr < n && nc >= 0 && nc < n && i * i + j * j == 5 && s[getIndex(nr, nc)] == X[idx+1]) {
        dfs(idx+1, nr, nc);
      }
    }
}

void work() {
  for (int i = 0 ; i < n ; i++)
    for (int j = 0 ; j < n ; j++)
      if (s[getIndex(i, j)] == X[0])
        dfs(0, i, j);
}

int main() {
  cin >> n;
  cin >> s;

  work();
  cout << "NO\n";
  return 0;
}