#include <bits/stdc++.h>
using namespace std;

set<long long> cur, s;

int main() {
    int n; scanf("%d", &n);

    for(int i = 1 ; i <= n ; i++) {
        set<long long> tmp;
        long long x; scanf("%lld", &x);

        for(long long y : cur) {
            tmp.insert(__gcd(y, x));
        }
        tmp.insert(x);

        for(long long y : tmp) {
            s.insert(y);
        }

        cur = tmp;
    }

    printf("%d\n", (int)s.size());
    return 0;
}