#include <bits/stdc++.h>
using namespace std;

const int N = 2005;

int n, m;
vector<int> a, b;

int get_dist(int a, int b) {
    int diff = abs(a-b);
    return min(diff, m - diff);
}

void read() {
    cin >> m >> n;
    a.resize(n+1);
    b.resize(n+1);

    for(int i = 1 ; i <= n ; i++) {
        cin >> a[i];
    }
    for(int i = 1 ; i <= n ; i++) {
        cin >> b[i];
    }
}

int solve(vector<int> &b) {
    int ret = 0;

    for(int i = 1 ; i < b.size() ; i++) {
        ret += get_dist(b[i-1], b[i]);
    }

    return ret;
}

int work() {
    int in_b = (a[1] + m/2) % m;
    int ret = 1e9;
    b[0] = m/2;

    for(int i = 1 ; i <= n+1 ; i++) {
        b.insert(b.begin() + i, in_b);
        ret = min(ret, solve(b));
        b.erase(b.begin() + i);
    }

    return ret;
}

int main() {
    read();
    int ret = work();

    cout << ret << endl;
    return 0;
}
