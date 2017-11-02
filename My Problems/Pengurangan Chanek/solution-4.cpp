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

long long solve() {
    if(n == 1) {
        return arr[0];
    }

    sort(arr, arr + n);
    long long ret = accumulate(arr, arr + n, 0ll) - 2 * arr[0];

    return ret;
}

int main() {
    read();
    cout << solve() << endl;
    return 0;
}
