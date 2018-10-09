#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;

int k, n;
int h[30];
string s, t;

void myAssert(bool x) {
    if(!x) while(1){}
}

int memo[100005][305];

int dp(int pos, int lft) {
    if (lft == k) {
        return 1;
    }
    if (pos >= n) {
        return 0;
    }

    int &ret = memo[pos][lft];
    if (ret == -1) {
        ret = dp(pos+1, lft);
        if (t[pos] == s[lft]) {
            ret = (ret + dp(pos+1+h[s[lft]-'A'], lft+1))%MOD;
        }
    }
    return ret;

}

int main() {
    memset(memo, -1, sizeof memo);

    cin >> k >> n;

    for (int i = 0; i < 26; i++) {
        long long x;
        cin >> x;
        x = min((long long)n, x);
        h[i] = x;
    }

    cin >> s >> t;
    myAssert(s.length() == k);
    myAssert(t.length() == n);

    for (char ch : s) {
        myAssert('A' <= ch && ch <= 'Z');
    }
    // for (char ch : s) {
    //     myAssert
    // }

    cout << dp(0, 0) << endl;

}   