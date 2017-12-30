#include <bits/stdc++.h>
using namespace std;

int n, r;
int x[1005];
double y[1005];

int sqr(int z) {
    return z * z;
}

void read() {
    cin >> n >> r;
    for(int i = 0 ; i < n ; i++) {
        cin >> x[i];
    }
}

double get_max(int idx) {
    //cout << idx << endl;
    double ret = r;

    //cout << ret << endl;

    for(int i = 0 ; i < idx ; i++) {
        if(abs(x[idx] - x[i]) <= 2 * r) {
            double cur = sqrt(sqr(2 * r) - sqr(x[idx] - x[i]));
            cur = y[i] + cur;

            //cout << ret << " " << cur << endl;

            ret = max(ret, cur);
        }
    }

    //cout << ret << endl;
    //printf("%d -> %.9lf\n", idx, ret);

    return ret;
}

void solve() {
    for(int i = 0 ; i < n ; i++) {
        y[i] = get_max(i);
        cout << setprecision(10) << fixed << y[i] << endl;
    }
}

int main() {
    read();
    solve();
    return 0;
}

