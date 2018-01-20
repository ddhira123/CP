#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int BIT[N];
vector<int> arr[3];
int n;

void update(int x, int val) {
    for(; x <= n ; x += x & -x) {
        BIT[x] += val;
    }
}

int query(int x) {
    int ret = 0;
    while(x) {
        ret += BIT[x];
        x -= x & -x;
    }
    return ret;
}

long long calc_inversion(vector<int> x, vector<int> y) {
    vector<int> pos(n+1);

    for(int i = 0 ; i < y.size() ; i++) {
        pos[y[i]] = i+1;
    }

    memset(BIT, 0, sizeof BIT);

    long long ret = 0;
    for(int i = x.size()-1 ; i >= 0 ; i--) {
        ret += query(pos[x[i]]);
        update(pos[x[i]], 1);
    }

    return ret;
}

void read() {
    scanf("%d", &n);
    for(int i = 0 ; i < 3 ; i++) {
        for(int j = 0 ; j < n ; j++) {
            int x; scanf("%d", &x);
            arr[i].push_back(x);
        } 
    }
}

long long work() {
    long long ret = 1ll * n * (n - 1) / 2;
    long long inve = 0;

    inve += calc_inversion(arr[0], arr[1]);
    // cout << calc_inversion(arr[0], arr[1]) << endl;

    inve += calc_inversion(arr[0], arr[2]);
    // cout << calc_inversion(arr[0], arr[2]) << endl;

    inve += calc_inversion(arr[1], arr[2]);
    // cout << calc_inversion(arr[1], arr[2]) << endl;

    ret -= inve / 2;

    return ret;
}

int main() {
    read();
    cout << work() << endl;
    return 0;
}