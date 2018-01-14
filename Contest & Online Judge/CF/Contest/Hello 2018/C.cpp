#include <bits/stdc++.h>
using namespace std;

const int N = 35;

int c[N];
int n, l;

void read() {
    cin >> n >> l;
    for(int i = 0 ; i < n ; i++) {
        cin >> c[i];
    }
}

long long solve() {
    vector<pair<int, int>> v;
    for(int i = 0 ; i < n ; i++) {
        v.push_back({1 << i, c[i]});
    }

    sort(v.begin(), v.end(), [&](pair<int, int> a, pair<int, int> b) {
        return 1ll * a.second * b.first < 1ll * a.first * b.second;
    });

    long long ret = 4e18;
    long long sum = 0;

    for(auto x : v) {
        int use = l / x.first;
        sum += 1ll * use * x.second;

        l %= x.first;

        if(l > 0) {
            ret = min(ret, sum + x.second);
        } else {
            ret = min(ret, sum);
        }
    }

    return ret;
}

int main() {
    read();
    cout << solve() << endl;
    return 0;
}