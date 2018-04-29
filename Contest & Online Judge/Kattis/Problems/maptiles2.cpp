#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    reverse(s.begin(), s.end());

    int x = 0, y = 0;
    int len = s.length();

    for(int i = len-1 ; i >= 0 ; i--) {
        char ch = s[i];

        if(ch == '1' || ch == '3') {
            x += (1 << i);
        }
        if(ch == '2' || ch == '3') {
            y += (1 << i);
        }
    }

    cout << len << " " << x << " " << y << endl;
    return 0;
}
