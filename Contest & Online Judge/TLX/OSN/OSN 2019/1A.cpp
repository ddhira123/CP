#include <bits/stdc++.h>
using namespace std;

const int RC = 1e5 + 5;

string readString() {
  static char s[RC];
  scanf("%s", s);
  return (string)s;
}

vector<vector<int>> psum;
int r, c;

void read() {
  scanf("%d %d", &r, &c);
  psum.resize(r+1, vector<int>(c+1, 0));

  for (int i = 1 ; i <= r ; i++) {
    string s = readString();
    for (int j = 1 ; j <= c ; j++) {
      psum[i][j] = s[j-1] - '0';
      psum[i][j] = psum[i][j] + psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
    }
  }
}

int getSum(int r1, int c1, int r2, int c2) {
  return psum[r2][c2] - psum[r1-1][c2] - psum[r2][c1-1] + psum[r1-1][c1-1];
}

int calc(int width) {
  int height = psum[r][c] / width;
  // printf("all %d width %d height %d\n", psum[r][c], width, height);
  if (width > c || height > r) return RC;

  int ret = RC;
  for (int i = 1 ; i + height - 1 <= r ; i++)
    for (int j = 1 ; j + width - 1 <= c ; j++) {
      ret = min(ret, psum[r][c] - getSum(i, j, i + height - 1, j + width - 1));
    }
  
  return ret;
}

int work() {
  int ret = RC;
  // printf("%d\n", psum[r][c]);
  for (int i = 1 ; i <= psum[r][c] ; i++) {
    if (psum[r][c] % i == 0) {
      ret = min(ret, calc(i));
    }
  }
  if (ret == RC) ret = -1;
  return ret;
}

int main() {
  read();
  printf("%d\n", work());
  return 0;
}
