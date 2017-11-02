#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e3 + 5;

int arr[N];
int n, k;

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", arr + i);
    }
}

int solve() {
    int ret = 0;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++) {
            ret += __gcd(arr[i], arr[j]);
            ret %= MOD;
        }
    return ret;
}

int main() {
    read();
    printf("%d\n", solve());
    return 0;
}
