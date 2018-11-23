#include <bits/stdc++.h>
using namespace std;

string a, b, c;

void read() {
  string dummy;
  cin >> a >> dummy >> b >> dummy >> c;
}

int calcQuestionMark(string x) {
  return count_if(x.begin(), x.end(), [](char ch) {
    return ch == '?';
  });
}

int arr[10];

int eval(vector<int> &v) {
  int ret = 0;
  for (int x : v) {
    ret = 10 * ret + x;
  }
  return ret;
}

int check() {
  int it = 0;
  vector<int> aa;
  for (char ch : a) {
    if (ch == '?') aa.push_back(arr[it++]);
    else aa.push_back(ch - '0');
  }

  vector<int> bb;
  for (char ch : b) {
    if (ch == '?') bb.push_back(arr[it++]);
    else bb.push_back(ch - '0');
  }

  if (aa.size() > 1 && aa[0] == 0) return 0;
  if (bb.size() > 1 && bb[0] == 0) return 0;

  int res = eval(aa) ^ eval(bb);
  vector<int> cc;
  while (res > 0) {
    cc.push_back(res % 10);
    res /= 10;
  }
  reverse(cc.begin(), cc.end());
  if (cc.empty()) cc.push_back(0);

  if (cc.size() != c.size()) return 0;
  for (int i = 0 ; i < c.size() ; i++) {
    if (cc[i]+'0' != c[i] && c[i] != '?') return 0;
  }

  return 1;
}

int rec(int pos, int question) {
  if (pos == question) {
    return check();
  } else {
    int ret = 0;
    for (int i = 0 ; i < 10 ; i++) {
      arr[pos] = i;
      ret += rec(pos+1, question);
    }
    return ret;
  }
}

int work() {
  if (calcQuestionMark(a) > calcQuestionMark(b)) swap(a, b);
  if (calcQuestionMark(a) > calcQuestionMark(c)) swap(a, c);
  if (calcQuestionMark(b) > calcQuestionMark(c)) swap(b, c);

  int question = calcQuestionMark(a) + calcQuestionMark(b);
  return rec(0, question);
}

int main() {
  read();
  cout << work() << endl;
  return 0;
}