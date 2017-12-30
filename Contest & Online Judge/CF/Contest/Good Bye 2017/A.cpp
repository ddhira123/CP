#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    int ret = 0;

    for(int i = 0 ; i < s.length() ; i++) {
        char chs[10] = {'a', 'i', 'u', 'e', 'o', '1', '3', '5', '7', '9'};

        int ok = 0;
        for(int j = 0 ; j < 10 ; j++) {
            ok |= (s[i] == chs[j]);
        }

        ret += ok;
    }

    cout << ret << endl;
    return 0;
}


