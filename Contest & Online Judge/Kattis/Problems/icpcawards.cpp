#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    set<string> s;

    for(int i = 0 ; i < n && s.size() < 12 ; i++) {
        string a, b;
        cin >> a >> b;

        if(!s.count(a)) {
            cout << a <<  " " << b << endl;
            s.insert(a);
        }
    }
    return 0;
}