#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

int arr[N];
int n;

void read() {
    cin >> n;
    for(int i = 1 ; i <= n ; i++) {
        cin >> arr[i];
    }
}

int solve() {
    int fpb = arr[1];
    int satu = 0;

    for(int i = 1 ; i <= n ; i++) {
        fpb = __gcd(fpb, arr[i]);
        satu += (arr[i] == 1);
    }

    if(fpb != 1) {
        return -1;
    }

    if(satu != 0) {
        return n - satu;
    }

    int ret = 1e9;
    for(int i = 1 ; i <= n ; i++) {
        int gcd = arr[i];
        int j = i;

        while(j < n && gcd != 1) {
            j++;
            gcd = __gcd(gcd, arr[j]);
        }

        // cout << i << " " << gcd << endl;

        if(gcd == 1) {
            ret = min(ret, j-i + n-1);
        }
    }

    return ret;
}

int main() {
    read();
    cout << solve() << endl;
    return 0;
}