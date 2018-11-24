#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 5;

int stringToInt(string s) {
  if (s == "0") return 0;
  int ret = 0;
  for (char ch : s) {
    ret = 10 * ret + (ch - '0');
  }
  return ret;
}

string getString() {
  static char s[105];
  scanf("%s", s);

  return (string)s;
}

bool isNum(char ch) {
  return '0' <= ch && ch <= '9';
}

void FAIL() {
  puts("NE");
  exit(0);
}

map<string, int> vals;
map<string, int> num;

string arr[2][N];
vector<pair<int, int>> idxs[2 * N];
bool udah[2 * N];
int n;

int getID(string s) {
  if (num.count(s)) return num[s];
  int sz = num.size();
  num[s] = sz;
  return sz;
}

void read() {
  scanf("%d", &n);
  for (int it = 0 ; it < 2 ; it++)
    for (int i = 0 ; i < n ; i++) {
      arr[it][i] = getString();
    }
}

void prepare() {
  for (int it = 0 ; it < 2 ; it++)
    for (int i = 0 ; i < n ; i++) {
      if (isNum(arr[it][i][0])) {
        vals[arr[it][i]] = stringToInt(arr[it][i]);
      }

      int id = getID(arr[it][i]);
      idxs[id].push_back({it, i});
    }
}

void dfs(int now) {
  if (udah[now]) {
    return;
  }
  udah[now] = 1;

  for (auto it : idxs[now]) {
    int row = it.first;
    int col = it.second;

    string opposite = arr[row^1][col];
    if (!vals.count(opposite)) {
      vals[opposite] = vals[arr[row][col]];
      dfs(getID(opposite));
    } else {
      if (vals[opposite] != vals[arr[row][col]]) {
        FAIL();
      }
    }
  }
}

void work() {
  for (int it = 0 ; it < 2 ; it++)
    for (int i = 0 ; i < n ; i++) {
      string cur = arr[it][i];
      int id = getID(cur);

      if (vals.count(cur) && !udah[id]) {
        dfs(id);
      }
    }
  
  puts("DA");
}

int main() {
  read();
  prepare();
  work();
  return 0;
}