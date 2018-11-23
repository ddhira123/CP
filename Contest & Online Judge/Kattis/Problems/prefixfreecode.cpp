#include <bits/stdc++.h>
using namespace std;

const int MAXS = 1e6 + 5;
const int MOD = 1e9 + 7;

string getString() {
  static char s[MAXS];
  scanf("%s", s);
  return (string)s;
}

struct Node {
  int nex[26];
  int sz;
  bool hasEnd;

  Node() {
    memset(nex, -1, sizeof nex);
    sz = 0;
    hasEnd = false;
  }
};

int fact[MAXS];

struct Trie {
  Node nod[MAXS];
  int sz;

  Trie() {
    sz = 0;
  }

  void add(string s) {
    int cur = 0;
    
    for (char ch : s) {
      nod[cur].sz++;
      int &nex = nod[cur].nex[ch - 'a'];
      // cout << s << " " << ch << " " << cur << " " << nex << endl;

      if (nex == -1) {
        nex = ++sz;
      }
      cur = nex;
    }

    // cout << cur << endl;
    nod[cur].hasEnd = true;
    nod[cur].sz++;
  }

  int solve(string s, int k) {
    int ret = 1;
    int idx = 0;

    for (int i = k ; i >= 1 ; i--) {
      int cur = 0;

      while (!nod[cur].hasEnd) {
        // cout << i << " " << idx << " " << cur << endl;
        nod[cur].sz--;
        assert(idx < s.length());

        int ch = s[idx] - 'a';
        idx++;

        for (int j = 0 ; j < ch ; j++) {
          int nxt = nod[cur].nex[j];
          if (nxt != -1) {
            // printf("step %d j %d sz %d fact %d\n", i, j, nod[nxt].sz, fact[i-1]);
            ret = (ret + 1ll * fact[i-1] * nod[nxt].sz) % MOD;
          }
        }

        // cout << cur << " " << ch << " eee " << nod[cur].nex[ch] << endl;
        cur = nod[cur].nex[ch];
        assert(cur != -1);
      }

      nod[cur].sz--;
      // idx++;
    }

    return ret;
  }
};

int n, k;
Trie t;

int main() {
  scanf("%d %d", &n, &k);
  fact[0] = 1;
  for (int i = 1 ; i <= k ; i++) {
    fact[i] = 1ll * fact[i-1] * (n - k + i) % MOD;
  }

  for (int i = 0 ; i < n ; i++) {
    string s = getString();
    t.add(s);
  }

  string s = getString();
  int ret = t.solve(s, k);
  printf("%d\n", ret);
  return 0;
}