#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

string getString() {
  static char s[N];
  scanf("%s", s);
  return (string)s;
}

struct Node {
  int nex[26];
  int active;
  int isEnd;

  Node() {
    memset(nex, -1, sizeof nex);
    active = isEnd = 0;
  }
};

Node trie[N];
int sz;

void add(string s) {
  int cur = 0;
  for (char ch : s) {
    trie[cur].active++;
    int &nxt = trie[cur].nex[ch - 'a'];
    if (nxt == -1) nxt = ++sz;
    cur = nxt;
  }
  trie[cur].isEnd = 1;
}

void init() {
  int n; scanf("%d", &n);
  for (int i = 0 ; i < n ; i++) {
    string s = getString();
    add(s);
  }
}

string solve(string s) {
  string ret = "";
  int cur = 0;
  for (int i = 0 ; i < s.length() ; ) {
    if (s[i] != '#') {
      ret += s[i];
      if (cur != -1) {
        cur = trie[cur].nex[s[i] - 'a'];
      }
      i++;
      continue;
    }

    int j = i;
    while (j < s.length() && s[i] == s[j]) {
      j++;
    }

    if (cur == -1 || trie[cur].active == 0) {
      i = j;
      continue;
    }

    int diff = j - i - 1;
    diff %= trie[cur].active;
    diff++;

    while (diff > 0) {
      // cout << i << " " << j << " " << diff << endl;
      // cout << ret << endl;

      for (int i = 0 ; i < 26 ; i++) {
        int nxt = trie[cur].nex[i];
        if (nxt == -1) continue;

        int tot = trie[nxt].active + trie[nxt].isEnd;
        if (tot < diff) {
          diff -= tot;
        } else {
          ret += (char)(i + 'a');
          cur = nxt;
          break;
        }
      }

      if (trie[cur].isEnd) {
        diff--;
      }
    }

    i = j;
  }

  return ret;
}

void work() {
  int q; scanf("%d", &q);
  for (int i = 0 ; i < q ; i++) {
    string s = getString();

    printf("%s\n", solve(s).c_str());
  }
}

int main() {
  init();
  work();
  return 0;
}