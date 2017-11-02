#include <bits/stdc++.h>
using namespace std;

set<string> seen;

int main() {
    int n; cin >> n;
    for(int i = 0 ; i < n ; i++) {
        string s;
        cin >> s;

        if(seen.count(s)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }

        seen.insert(s);
    }
    return 0;
}