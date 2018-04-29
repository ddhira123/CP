#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int k, n;
int arr[N];
int act[N];

int all_sum[N];
int act_sum[N];

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &arr[i]);
    }
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &act[i]);
    }
}

void prepare() {
    for(int i = 1 ; i <= n ; i++) {
        all_sum[i] = all_sum[i-1] + arr[i];
        act_sum[i] = act_sum[i-1] + (act[i] ? arr[i] : 0);
    }
}

int work() {
    int mx = -1;

    for(int i = 1 ; i+k-1 <= n ; i++) {
        int lsum = act_sum[i-1];
        int rsum = act_sum[n] - act_sum[i+k-1];
        int msum = all_sum[i+k-1] - all_sum[i-1];

        int sums = lsum + rsum + msum;
        mx = max(mx, sums);
    }

    return mx;
}

int main() {
    read();
    prepare();
    cout << work() << endl;
    return 0;
}