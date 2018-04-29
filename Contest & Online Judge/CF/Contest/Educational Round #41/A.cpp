#include <bits/stdc++.h>
using namespace std;

const int N = 1005;

int cnt[N];
int n, m;

int main() {
    cin >> n >> m;
    for(int i = 0 ; i < m ; i++) {
        int x; cin >> x;
        cnt[x]++;
    }

    int mins = 1e9;
    for(int i = 1 ; i <= n ; i++) {
        mins = min(mins, cnt[i]);
    }

    cout << mins << endl;
    return 0;
}