#include <bits/stdc++.h>
using namespace std;

const int MX = 256;

int ans[MX];

void precompute() {
    for(int i = 0 ; i < MX ; i++) {
        ans[(i ^ (i << 1)) & (MX-1)] = i;
    }
}

int main() {
    precompute();
    int n; scanf("%d", &n);

    for(int i = 1 ; i <= n ; i++) {
        int x; scanf("%d", &x);
        x = ans[x];

        printf("%d%c", x, i == n ? '\n' : ' ');
    }
    return 0;
}