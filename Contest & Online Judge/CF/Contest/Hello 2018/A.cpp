#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> n >> m;

    if(n < 30) {
        m %= (1 << n);
    } 

    cout << m << endl;
    return 0;
}