#include <bits/stdc++.h>
using namespace std;

const int N = 3005;

int arr[N];
int n, k;

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", arr + i);
    }
}

int solve() {
    int ret = 0;
    for(int i = 1 ; i <= n ; i++)
        for(int j = i ; j <= n && arr[j] == arr[i] ; j++) {
            ret++;
        }
    return ret;
}

int main() {
    read();
    cout << solve() << endl;
    return 0;
}
