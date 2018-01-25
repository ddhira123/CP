#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MX = 1e6 + 5;

pair<int, int> arr[N];
int n, x;

void read() {
    scanf("%d %d", &n, &x);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d %d", &arr[i].first, &arr[i].second);
    }
}

void solve() {
    sort(arr, arr + n);
    int ret = 1e9;

    int it = 0;
    int minus = 0;

    for(int i = x ; i < MX ; i++) {
        while(it < n && arr[it].first <= i) {
            minus += arr[it].second;
            it++;
        }

        ret = min(ret, i - minus);
    }

    printf("%d\n", ret);
}

int main() {
    read();
    solve();
    return 0;
}