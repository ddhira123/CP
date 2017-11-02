#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n;
int arr[N];

void read() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
    }
}

void rec(int now, int mask, long long sum, long long &ret) {
    if(now == n) {
        if(mask == 3) {
            ret = max(ret, sum);
        }
    } else {
        rec(now+1, mask | 1, sum + arr[now], ret);
        rec(now+1, mask | 2, sum - arr[now], ret);
    }
}

long long solve() {
    if(n == 1) {
        return arr[0];
    }

    long long ret = -4e18;
    rec(0, 0, 0, ret);

    return ret;
}

int main() {
    read();
    cout << solve() << endl;
    return 0;
}
