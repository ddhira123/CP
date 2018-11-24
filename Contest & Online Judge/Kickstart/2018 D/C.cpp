#include <bits/stdc++.h>
using namespace std;

const int W = 10005;
const int R = 102;
const int C = 102;

long long val[R][C][R][C];
string str[R];
string word[W];
int r, c, w;

int back[W];

long long gcd(long long a, long long b) {
  return b ? gcd(b, a % b) : a;
}

void build(string s) {
  int i = 0;
  int j = -1;
  back[0] = -1;

  while(i < s.length()) {
    while(j >= 0 && s[i] != s[j]) j = back[j];
    i++; j++;
    back[i] = j;
  }
}

void read() {
  cin >> r >> c >> w;
  for(int i = 1 ; i <= r ; i++) {
    cin >> str[i];
    str[i] = "." + str[i];
    // cout << str[i].length() << endl;
  }
  for(int i = 1 ; i <= w ; i++) {
    cin >> word[i] ;
    // cout << word[i].length() << "asd " << endl;
  }
    // cin >> word[i];
}

void prepare() {
  for (int i = 1; i <= r; i++)
    for (int j = i; j <= r; j++)
      for (int k = 1; k <= c; k++)
        for (int l = k; l <= c; l++) {
          val[i][j][k][l] = 0;
        }
  
  for(int i = 1 ; i <= w ; i++) {
    for(int times = 0 ; times < 2 ; times++) {
      build(word[i]);

      for(int row = 1 ; row <= r ; row++) {
        int j = 1, k = 0;

        while(j <= c) {
          while(k >= 0 && str[row][j] != word[i][k]) k = back[k];
          k++;

          if(k == word[i].length()) {
            val[row][row][j - word[i].length() + 1][j] += word[i].length();
            k = back[k];
          }
          j++;
        }
      }

      for(int col = 1 ; col <= c ; col++) {
        int j = 1, k = 0;

        while(j <= r) {
          while(k >= 0 && str[j][col] != word[i][k]) k = back[k];
          k++;

          if(k == word[i].length()) {
            val[j - word[i].length() + 1][j][col][col] += word[i].length();
            k = back[k];
          }
          j++;
        }
      }

      reverse(word[i].begin(), word[i].end());
    }
  }

  for(int lenRow = 1 ; lenRow <= r ; lenRow++)
    for(int row = 1 ; row + lenRow - 1 <= r ; row++)
      for(int lenCol = 1 ; lenCol <= c ; lenCol++)
        for(int col = 1 ; col + lenCol - 1 <= c ; col++) {
          int row2 = row + lenRow - 1;
          int col2 = col + lenCol - 1;

          for(int i = 0 ; i <= 1 ; i++)
            for(int j = 0 ; j <= 1 ; j++)
              for(int k = 0 ; k <= 1 ; k++)
                for(int l = 0 ; l <= 1 ; l++) {
                  if(i == 0 && j == 0 && k == 0 && l == 0) continue;
                  
                  int atas = row + i;
                  int bawah = row2 - j;
                  int kiri = col + k;
                  int kanan = col2 - l;

                  if(atas <= bawah && kiri <= kanan) {
                    int sign = (i + j + k + l) % 2 ? 1 : -1;
                    val[row][row2][col][col2] += sign * val[atas][bawah][kiri][kanan];
                  } 
                }
        }
}

void work() {
  long long atas = 0, bawah = 1;
  int way = 0;

  // cout << "masuk\n";
  for(int i = 1 ; i <= r ; i++)
    for(int j = i ; j <= r ; j++)
      for(int k = 1 ; k <= c ; k++)
        for(int l = k ; l <= c ; l++) {
          long long tot = val[i][j][k][l];
          long long totdiv = j - i + 1 + l - k + 1;

          if (bawah * tot == atas * totdiv)
            way++;
          else if (bawah * tot > atas * totdiv) {
            way = 1;
            atas = tot;
            bawah = totdiv;
          }
        }

  int fpb = gcd(atas, bawah);
  printf("%lld/%lld %d\n", atas / fpb, bawah / fpb, way);
}

int main() {
  int t; cin >> t;
  for(int tc = 1 ; tc <= t ; tc++) {
    cerr << "now " << tc << endl;
    read();
    // if(tc <= 91) continue;
    prepare();

    printf("Case #%d: ", tc);
    work();
  }
  return 0;
}