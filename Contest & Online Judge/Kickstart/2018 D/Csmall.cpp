#include <bits/stdc++.h>
using namespace std;

const int W = 1005;
const int R = 105;
const int C = 105;

int val[R][C];
string str[R];
string word[R];
int r, c, w;

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

void read() {
  cin >> r >> c >> w;
  for(int i = 1 ; i <= r ; i++) {
    cin >> str[i];
    str[i] = "." + str[i];
  }
  for(int i = 1 ; i <= w ; i++)
    cin >> word[i];
}

void prepare() {
  memset(val, 0, sizeof val);
  
  for(int i = 1 ; i <= w ; i++) {
    for(int row = 1 ; row <= r ; row++)
      for(int col = 1 ; col <= c ; col++) {
        if(word[i][0] == str[row][col])
          val[row][col] = 4;
      }
  }

  for(int i = 1 ; i <= r ; i++)
    for(int j = 1 ; j <= c ; j++) {
      val[i][j] = (val[i][j] + val[i-1][j] + val[i][j-1] - val[i-1][j-1]);
    }
}

void work() {
  int atas = 0, bawah = 1;
  int way = 0;

  for(int i = 1 ; i <= r ; i++)
    for(int j = i ; j <= r ; j++)
      for(int k = 1 ; k <= c ; k++)
        for(int l = k ; l <= c ; l++) {
          int tot = val[j][l] - val[i-1][l] - val[j][k-1] + val[i-1][k-1];
          int totdiv = j - i + 1 + l - k + 1;

          if(bawah * tot == atas * totdiv)
            way++;
          else if(bawah * tot > atas * totdiv) {
            way = 1;
            atas = tot;
            bawah = totdiv;
          }
        }
  
  int fpb = gcd(atas, bawah);
  printf("%d/%d %d\n", atas / fpb, bawah / fpb, way);
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    cerr << "now " << tc << endl;
    read();
    prepare();

    printf("Case #%d: ", tc);
    work();
  }
  return 0;
}