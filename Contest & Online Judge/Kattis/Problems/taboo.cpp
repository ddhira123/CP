#include <bits/stdc++.h>
using namespace std;

const int MAXS = 3e5 + 5;

string getString() {
  static char s[MAXS];
  scanf("%s", s);
  return (string)s;
}

struct Node {
  int fail;
  int nex[2];
  bool hasEnd;

  Node() {
    hasEnd = 0;
    nex[0] = nex[1] = -1;
  }
};

struct AhoCorasick {
  Node nod[MAXS];
  int dp[MAXS];
  int vis[MAXS];
  int sz;

  AhoCorasick() {
    sz = 0;
  }

  void add(string s) {
    int cur = 0;
    for (char ch : s) {
      int idx = ch - '0';
      int &nex = nod[cur].nex[idx];

      if (nex == -1)
        nex = ++sz;
      cur = nex;
    }
    nod[cur].hasEnd = true;
  }

  void build() {
    queue<int> q;

    nod[0].fail = 0;
    for (int i = 0 ; i < 2 ; i++) {
      int &nex = nod[0].nex[i];
      if (nex == -1)
        nex = 0;
      else {
        nod[nex].fail = 0;
        q.push(nex);
      }
    }

    while (!q.empty()) {
      int now = q.front();
      int fail = nod[now].fail;
      q.pop();

      nod[now].hasEnd |= nod[fail].hasEnd;

      for (int i = 0 ; i < 2 ; i++) {
        int &nex = nod[now].nex[i];
        if (nex == -1)
          nex = nod[fail].nex[i];
        else {
          nod[nex].fail = nod[fail].nex[i];
          q.push(nex);
        }
      }
    }
  }

  string solve() {
    memset(dp, -1, sizeof dp);
    memset(vis, -1, sizeof vis);
    bool cycle = false;

    function<int(int)> dfs = [&](int now) {
      if (nod[now].hasEnd) return (int)-1;
      if (vis[now] == 2) {
        cycle = 1;
        return -1;
      }
      if (vis[now] == 1) return dp[now];

      vis[now] = 2;
      int &ret = dp[now];
      ret = 0;
      for (int i = 0 ; i < 2 ; i++) {
        ret = max(ret, dfs(nod[now].nex[i]) + 1);
      }
      
      vis[now] = 1;
      return ret;
    };

    int len = dfs(0);
    if (cycle) return "-1";

    string ret = "";
    int now = 0;

    for (int i = 0 ; i < len ; i++) {
      for (int j = 0 ; j < 2 ; j++) {
        int nex = nod[now].nex[j];
        if (dp[now] == dp[nex] + 1) {
          ret += (char)('0' + j);
          now = nex;
          break;
        }
      }
    }

    return ret;
  }
};

int n;
AhoCorasick ac;

int main() {
  scanf("%d", &n);
  for (int i = 0 ; i < n ; i++) {
    string s = getString();
    ac.add(s);
  }
  ac.build();
  printf("%s\n", ac.solve().c_str());
  return 0;
}