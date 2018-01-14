#include <bits/stdc++.h>
using namespace std;

long long rec(long long x) {
    if(x % 4 == 0) return x;
    if(x % 4 == 3) return 0;
    return x ^ rec(x - 1);
}

int main() {
    int t; scanf("%d", &t);
    for(int tc = 1 ; tc <= t ; tc++) {
        long long l, r;
        scanf("%lld %lld", &l, &r);

        printf("%lld\n", rec(r) ^ rec(l-1));
    }
    return 0;
}