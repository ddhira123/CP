#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e5 + 5;

int arr[N];
int n, k;

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", arr + i);
    }
}

int solve() {
    int ret = arr[0];

    for(int i = 0 ; i < (1 << k) ; i++) {
        ret = (1ll * ret * n) % MOD;
    }
    
    return ret;
}

int main() {
    read();
    printf("%d\n", solve());
    return 0;
}
