#include <bits/stdc++.h>
using namespace std;

const char LOW = 'a';
const char HIGH = 'z';

int calc(char ch, string &s) {
    int ret = 0;

    for(char x : s)
        ret += (x != ch);
    
    return ret;
}

int solve(string &s) {
    int ret = 1e9;

    for(char i = LOW ; i <= HIGH ; i++) {
        ret = min(ret, calc(i, s));
    }

    return ret;
}

int main() {
    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        int n; cin >> n;
        string s; cin >> s;

        int ret = solve(s);
        cout << ret << "\n";
    }
    return 0;
}