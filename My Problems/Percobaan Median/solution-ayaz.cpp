#include <bits/stdc++.h>
using namespace std;

const int N = 50005;

int arr[2][N];
int n, k;

void read() {
    scanf("%d %d", &n, &k);
    for(int it = 0 ; it < 2 ; it++) {
        for(int i = 1 ; i <= n ; i++)
            scanf("%d", &arr[it][i]);
    }
}


vector<int> make(int idx, int lmt) {
    vector<int> ret;

    int sum = 0;
    for(int i = 1 ; i <= k ; i++)
        sum += (arr[idx][i] <= lmt) ? 1 : -1;

    ret.push_back(sum);
    for(int i = k+1 ; i <= n ; i++) {
        sum += (arr[idx][i] <= lmt) ? 1 : -1;
        sum -= (arr[idx][i-k] <= lmt) ? 1 : -1;

        ret.push_back(sum);
    }

    return ret;
}

long long check(int lmt) {
    vector<int> one = make(0, lmt);
    vector<int> two = make(1, lmt);

    sort(one.begin(), one.end());
    sort(two.begin(), two.end());

    long long ret = 0;
    int pos = two.size();
    for(int x : one) {
        while(pos > 0 && two[pos-1] + x > 0) {
            pos--;
        }
        ret += (two.size() - pos);
    }

    return ret;
}

int solve() {
    int lo = 1;
    int hi = 1e9;

    long long tgt = (n - k + 1);
    tgt *= tgt;
    tgt = (tgt / 2) + 1;

    while(lo < hi) {
        int mid = (lo + hi) / 2;

        if(check(mid) >= tgt) {
            hi = mid;
        } else {
            lo = mid+1;
        }
    }

    return lo;
}

int main() {
    int t;
    scanf("%d", &t);

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        printf("%d\n", solve());       
    }
    return 0;
}
