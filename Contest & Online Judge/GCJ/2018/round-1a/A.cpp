#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int r, c, h, v;
string arr[N];
int psum[N][N];

void read() {
  cin >> r >> c >> h >> v;
  for(int i = 0 ; i < r ; i++) {
    cin >> arr[i];
  }
}

void prepare() {
  for(int i = 1 ; i <= r ; i++) {
    for(int j = 1 ; j <= c ; j++) {
      psum[i][j] = psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
      psum[i][j] += (arr[i-1][j-1] == '@');
    }
  }
}

int get_sum(int r1, int r2, int c1, int c2) {
  return psum[r2][c2] - psum[r1-1][c2] - psum[r2][c1-1] + psum[r1-1][c1-1];
}

vector<int> get_horizontals() {
  vector<int> hors = {0};

  for(int i = 1 ; i <= r ; i++) {
    int r1 = hors.back()+1;
    int r2 = i;
    int c1 = 1;
    int c2 = c;

    if(get_sum(r1, r2, c1, c2) == psum[r][c] / (h + 1)) {
      while(i <= r && get_sum(r1, i, 1, c) == psum[r][c] / (h + 1)) {
        i++;
      }
      i--;

      hors.push_back(i);
    }
  }

  return hors;
}

vector<int> get_verticals() {
  vector<int> vers = {0};
  
  for (int i = 1; i <= c; i++) {
    int r1 = 1;
    int r2 = r;
    int c1 = vers.back()+1;
    int c2 = i;

    if (get_sum(r1, r2, c1, c2) == psum[r][c] / (v + 1)) {
      while(i <= c && get_sum(1, r, c1, i) == psum[r][c] / (v+1)) {
        i++;
      }
      i--;

      vers.push_back(i);
    }
  }

  return vers;
}

bool work() {
  if(psum[r][c] % ((h+1) * (v+1)) != 0) {
    return false;
  }
  int part = psum[r][c] / ((h+1) * (v+1));
  if(part == 0) {
    return true;
  }

  vector<int> vers = get_verticals();
  vector<int> hors = get_horizontals();

  if(vers.size() != v+2 || vers.back() != c) {
    return false;
  }
  if(hors.size() != h+2 || hors.back() != r) {
    return false;
  }

  for(int i = 1 ; i < hors.size() ; i++) {
    for(int j = 1 ; j < vers.size() ; j++) {
      int r1 = hors[i-1]+1;
      int r2 = hors[i];
      int c1 = vers[j-1]+1;
      int c2 = vers[j];

      if(get_sum(r1, r2, c1, c2) != part) {
        return false;
      }
    }
  }

  return true;
}

bool work2() {
  for(int i = 1 ; i < r ; i++) {
    for(int j = 1 ; j < c ; j++) {
      int a = get_sum(1, i, 1, j);
      int b = get_sum(i+1, r, 1, j);
      int e = get_sum(1, i, j+1, c);
      int f = get_sum(i+1, r, j+1, c);

      if(a == b && b == e && e == f) {
        return true;
      }
    }
  }

  return false;
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    read();
    prepare();
    printf("Case #%d: %s\n", tc, work() ? "POSSIBLE" : "IMPOSSIBLE");
  }
  return 0;
}