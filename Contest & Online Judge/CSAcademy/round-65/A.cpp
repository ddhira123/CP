#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, p;
    cin >> s >> p;

    for(int i = 0 ; i < s.length() ; i++) {
        s[i] = p[s[i] - 'a'];
    }

    cout << s << endl;
    return 0;
}