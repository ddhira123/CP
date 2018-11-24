#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int P = 105;

struct AhoCorasick {
  int trie[N*P][2];
  int fail[N*P];
  int akhir[N*P];
  long long dp[N * P][N];
  int saiz;

  void reset() {
    memset(trie, 0, sizeof trie);
    memset(fail, 0, sizeof fail);
    memset(akhir, 0, sizeof akhir);
    saiz = 1;

    trie[0][0] = 0;
    trie[0][1] = 0;
  }

  void addString(string s) {
    int cur = 1;
    for (char ch : s) {
      int asd = ch == 'R' ? 1 : 0;
      int &nex = trie[cur][asd];
      if (nex == 0) nex = ++saiz;
      cur = nex;
    }
    akhir[cur] = true;
  }

  void build() {
    queue<int> q;

    for (int i = 0 ; i < 2 ; i++) {
      if (trie[0][i] == -1) {
        trie[0][i] = 0;
      } else {
        fail[trie[0][i]] = 0;
        q.push(trie[0][i]);
      }
    }

    while(!q.empty()) {
      int now = q.front();
      q.pop();

      akhir[now] |= akhir[fail[now]];

      for (int i = 0 ; i < 2 ; i++) {
        int &nex = trie[now][i];

        if (nex == -1) {
          nex = trie[fail[now]][i];
        } else {
          fail[nex] = trie[fail[now]][i];
          q.push(nex);
        }
      }
    }
  }

  long long solve(int now, int sisa) {
    if (akhir[now]) return 0;
    if (sisa == 0) return 1;

    long long &ret = dp[now][sisa];
    if (ret != -1) return ret;

    ret = 0;
    for (int i = 0 ; i < 2 ; i++)
      ret += solve(trie[now][i], sisa-1);
    return ret;
  }

  long long work(int n) {
    memset(dp, -1, sizeof dp);
    return solve(1, n);
  }
};

AhoCorasick ac;
int n, p;

void init() {
  cin >> n >> p;
  ac.reset();

  for (int i = 0 ; i < p ; i++) {
    string s; cin >> s;
    ac.addString(s);
  }

  // ac.build();
}

int main() {
  int t; cin >> t;

  for (int tc = 1 ; tc <= t ; tc++) {
    init();

    long long ret = ac.work(n);
    printf("Case #%d: %lld\n", tc, ret);
  }
  return 0;
}