#include <bits/stdc++.h>
using namespace std;

const int N = 30;

int a[N], b[N];
int n, m;

void read() {
    cin >> n >> m;
    for(int i = 0 ; i < n ; i++) cin >> a[i];
    for(int i = 0 ; i < m ; i++) cin >> b[i];
}

void solve() {
    sort(a, a + n);
    sort(b, b + m);

    int ansa = 0, ansb = 0;
    for(int i = 1 ; min(n, m)-i >= 0 ; i++) {
        if(a[n-i] > b[m-i]) {
            ansa++;
        } else {
            ansb++;
        }
    }

    cout << ansa << " " << ansb << endl;
}

int main() {
    read();
    solve();
    return 0;
}