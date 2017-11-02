#include <bits/stdc++.h>
using namespace std;

int sz;
string s;

void solve() {
    int mx = 0;
    int sum = 0;
    for(int i = 0 ; i < s.length() ; i++) {
        if(s[i] == 'a') {
            sum++;
        } else {
            sum = 0;
        }

        mx = max(mx, sum);
    }

    for(int i = 0 ; i <= mx ; i++) {
        printf("a");
    }

    puts("");
}

int main() {
    cin >> s;
    solve();
    return 0;
}