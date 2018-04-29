#include <bits/stdc++.h>
using namespace std;

const int N = 25;

int arr[N];
int n;

int main() {
    cin >> n;
    for(int i = 0 ; i < n ; i++) cin >> arr[i];

    sort(arr, arr + n);
    double ret = arr[0];

    for(int i = 1 ; i < n ; i++) {
        ret = (ret + arr[i]) / 2;
    }

    printf("%.9lf\n", ret);
    return 0;
}