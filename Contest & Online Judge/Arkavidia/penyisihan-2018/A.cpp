#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; 
    scanf("%d", &t);

    for(int tc = 1 ; tc <= t ; tc++) {
        long long sum = 0;
        int mins = 1e7;

        int n; scanf("%d", &n);
        for(int i = 0 ; i < n ; i++) {
            int x; scanf("%d", &x);
            sum += x;
            mins = min(mins, x);
        }

        long long ret = sum - 1ll * mins * n;

        printf("%lld\n", ret);
    }
    return 0;
}