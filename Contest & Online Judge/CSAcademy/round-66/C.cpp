#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 5;

int cnt[MX];
int n, t;

void read() {
    scanf("%d %d", &n, &t);
    for(int i = 0 ; i < n ; i++) {
        int x; scanf("%d", &x);
        cnt[x]++;
    }
}

void solve() {
    for(int i = t ; i >= 1 ; i--) {
        for(int j = i + i ; j <= t ; j += i) {
            cnt[j] += cnt[i];
        }
    }

    int mx = -1;
    int tot = 0;

    for(int i = 1 ; i <= t ; i++) {
        if(cnt[i] > mx) {
            mx = cnt[i];
            tot = 1;
        } else if(cnt[i] == mx) {
            tot++;
        }
    }

    printf("%d %d\n", mx, tot);
}

int main() {
    read();
    solve();
    return 0;
}