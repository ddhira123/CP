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
    long long positive = accumulate(arr, arr + n, 0ll);
    long long negative = 0;
    long long ret = -4e18;

    for(int i = 0 ; i+1 < n ; i++) {
        positive -= arr[i];
        negative += arr[i];

        ret = max(ret, positive - negative);
    }

    return ret;
}

int main() {
    read();
    cout << solve() << endl;
    return 0;
}
