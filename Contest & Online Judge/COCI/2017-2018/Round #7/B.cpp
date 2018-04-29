#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, m, k;
int ans[N];

void read() {
    cin >> n >> k >> m;
}

void work() {
    long long loop = n + n - 2;
    loop *= k;

    int use = m / loop;
    int sisa = m % loop;

    ans[0] = ans[n-1] = use * k;
    for(int i = 1 ; i < n-1 ; i++) {
        ans[i] = 2 * use * k;
    }

    // cout << use << " " << sisa << " " << m << " " << loop << endl;

    for(int i = 0 ; i < n ; i++) {
        ans[i] += min(sisa, k);
        sisa -= min(sisa, k);
    }
    for(int i = n-2 ; i >= 0 ; i--) {
        ans[i] += min(sisa, k);
        sisa -= min(sisa, k);
    }

    for(int i = 0 ; i < n ; i++) {
        printf("%d%c", ans[i], i+1 == n ? '\n' : ' ');
    }
}

int main() {
    read();
    work();
    return 0;
}