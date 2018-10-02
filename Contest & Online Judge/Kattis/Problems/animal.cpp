#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;

int pwr[N][2];
vector<int> adj[N][2];
int val[N][2][2];
int sz[N][2];
set<pair<int, pair<int, int>>> sets[2];
int n;
string str[2];

void init() {
  pwr[0][0] = pwr[0][1] = 1;
  for(int i = 1 ; i < N ; i++) {
    pwr[i][0] = 2ll * pwr[i - 1][0] % MOD1;
    pwr[i][1] = 2ll * pwr[i - 1][1] % MOD2;
  }
}

void parse(int idx) {
  string s = str[idx];
  int i = 0;
  int cntr = 0;
  vector<int> stek;

  while(i < s.length()) {
    if(s[i] == '(') {
      if (!stek.empty()) {
        adj[stek.back()][idx].push_back(cntr);
      }

      stek.push_back(cntr);
      cntr++;
      i++;
    } else if (s[i] == ')') {
      stek.pop_back();
      i++;
    } else if (s[i] == ',') {
      i++;
    } else {
      assert(!stek.empty());
      adj[stek.back()][idx].push_back(cntr);

      string num = "";
      while ('0' <= s[i] && s[i] <= '9') {
        num += s[i];
        i++;
      }

      int numInt = stoi(num);
      val[cntr][idx][0] = pwr[numInt][0];
      val[cntr][idx][1] = pwr[numInt][1];

      cntr++;
    }
  }
}

void dfs(int idx, int now) {
  sz[now][idx] = 1;
  for(int nex : adj[now][idx]) {
    dfs(idx, nex);

    sz[now][idx] += sz[nex][idx];
    val[now][idx][0] = (val[now][idx][0] + val[nex][idx][0]) % MOD1;
    val[now][idx][1] = (val[now][idx][1] + val[nex][idx][1]) % MOD2;
  }

  pair<int, pair<int, int>> signature = {sz[now][idx], {val[now][idx][0], val[now][idx][1]}};
  sets[idx].insert(signature);
}

void prepare() {
  for(int i = 0 ; i < 2 ; i++) {
    parse(i);
    dfs(i, 0);
  }
}

int main() {
  init();
  cin >> n;
  cin >> str[0];
  cin >> str[1];

  if(n == 1) {
    cout << 1 << endl;
    return 0;
  }

  prepare();
  int ret = 0;
  for(auto x : sets[0]) {
    if (sets[1].count(x))
      ret++;
  }

  printf("%d\n", ret);
  return 0;
}