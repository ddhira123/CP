#include <bits/stdc++.h>
using namespace std;

const int MX = 1e9;
const int MUL = 1e7;

long long H(long long previousHash, string &transaction, long long token) {
  long long v = previousHash;
  for (int i = 0; i < transaction.length(); i++) {
    v = (v * 31 + transaction[i]) % 1000000007;
  }
  return (v * 7 + token) % 1000000007;
}

pair<string, int> getToken(int previousHash) {
  string transaction = "a";
  long long h = H(previousHash, transaction, 0);

  for (int i = 1 ; ; i++) {
    int tgt = i * MUL;
    int sisa = (tgt - h + 1000000007) % 1000000007;
    if (sisa < MUL) {
      return {transaction, sisa};
    }
  }
}

int main() {
  int n ; cin >> n;

  for (int i = 0 ; i < 2 ; i++) {
    pair<string, int> res = getToken(n);

    int nxt = H(n, res.first, res.second);
    n = nxt;
    // printf("%d\n", n);
    printf("%s %d\n", res.first.c_str(), res.second);
  }
  return 0;
}