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
    long long ret = -4e18;

    for(int i = 0 ; i+1 < n ; i++) {
        long long sum = 0;
        for(int j = 0 ; j <= i ; j++) {
            sum -= arr[j];
        }
        for(int j = i+1 ; j < n ; j++) {
            sum += arr[j];
        }
        ret = max(ret, sum);
    }

    return ret;
}

int main() {
    read();
    cout << solve() << endl;
    return 0;
}
