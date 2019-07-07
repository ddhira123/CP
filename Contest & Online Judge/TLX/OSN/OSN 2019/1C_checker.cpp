#include <bits/stdc++.h>
using namespace std;


vector<string> s;
string path;
int r, c;

vector<string> contestant;

int dp[1005][1005];

void wa(string reason) {
  cout << "Wrong Answer -- " + reason + "\n";
  exit(0);
}

void ac() {
  cout << "AC\n";
  exit(0);
}

void readInstance(ifstream &is) {
  is >> r >> c;
  is >> path;
  
  for (int i = 0 ; i < r ; i++) {
    string cur;
    is >> cur;
    s.push_back(cur);
  }
}

void readCon(ifstream &is) {
  for (int i = 0 ; i < r ; i++) {
    string cur;
    if (!(is >> cur)) wa("Kurang baris");
    if (cur.size() != c) wa("Panjang string salah");
    contestant.push_back(cur);
  }
  
  string dummy;
  if (is >> dummy) wa("Baris bablas");
}

void checkValidMap() {
  for (int i = 0 ; i < r ; i++) {
    for (int j = 0 ; j < c ; j++) {
      if (s[i][j] == '#') {
        if (contestant[i][j] != '#') wa("Invalid ganti pagar");
      } else {
        if (contestant[i][j] != 'x' && contestant[i][j] != '.') wa("Invalid ganti kosong");
      }
    }
  }

  if (contestant[0][0] != '.') wa("Rute juri ditutup");
  for (int i = 0 , nr = 0, nc = 0 ; i < path.size() ; i++) {
    if (path[i] == '>') nc++;
    else nr++;

    if (contestant[nr][nc] != '.') wa("Rute juri ditutup");
  }
}

void checkSingleWay() {
  dp[0][0] = 1;
  for (int i = 0 ; i < r ; i++)
    for (int j = 0 ; j < c ; j++) {
      if (contestant[i][j] == '.') {
        if (i == 0 && j == 0) continue;
        if (i > 0) dp[i][j] += dp[i-1][j];
        if (j > 0) dp[i][j] += dp[i][j-1];
        dp[i][j] = min(dp[i][j], 2);
      }
    }
  if (dp[r-1][c-1] != 1) wa("Tidak tepat satu rute");
}

int main(int argc, char** argv) {
  assert(argc == 3);

  ifstream instanceStream(argv[1]);
  ifstream conStream(argv[2]);

  readInstance(instanceStream);
  readCon(conStream);

  checkValidMap();
  checkSingleWay();
  ac();
  return 0;
}
