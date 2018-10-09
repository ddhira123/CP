#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n;
int arr[N];

int main() {
    scanf("%d", &n);
    for (int i = 1 ; i <= n ; i++) {
        scanf("%d", &arr[i]);
    }
    sort(arr + 1, arr + n + 1);

    bool ok = false;
    if (n == 1) {
        ok = true;
    } else {
        if (n % 3 == 2) {
            ok = (arr[n-1] == 1);
        } else if (n % 3 == 0) {
            ok = (arr[n] != 1 && arr[n-1] <= 2 && arr[n-2] == 1);
        } else {
            ok = (arr[n-1] <= 2 && arr[n-2] == 1);
        }
    }

    printf("%s\n", ok ? "Win" : "Lose");
    return 0;
}