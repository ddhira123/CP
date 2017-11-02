#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int arr[N];
int n, k;

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", arr + i);
    }
}

long long solve() {
    long long ret = 0;
    int lst = -1;
    int cur = 0;

    for(int i = 1 ; i <= n ; i++) {
        if(arr[i] != lst) {
            lst = arr[i];
            cur = 1;
        } else {
            cur++;
        }

        ret += cur;
    }

    return ret;
}

int main() {
    read();
    cout << solve() << endl;
    return 0;
}
