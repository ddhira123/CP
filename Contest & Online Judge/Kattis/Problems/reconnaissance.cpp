#include <bits/stdc++.h>
using namespace std;

const int TRIAL = 100;
const double MX = 1e6;
const int N = 1e5 + 5;

int x[N], v[N];
int n;

void read() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d %d", &x[i], &v[i]);
    }
}

double calc(double t) {
    double mins = x[0] + v[0] * t;
    double maks = mins;

    for(int i = 0 ; i < n ; i++) {
        double cur = x[i] + v[i] * t;
        mins = min(mins, cur);
        maks = max(maks, cur);
    }

    return maks - mins;
}

double work() {
    double lo = 0, hi = MX;

    for(int i = 0 ; i < TRIAL ; i++) {
        double p1 = lo + (hi - lo) / 3;
        double p2 = lo + 2 * (hi - lo) / 3;

        if(calc(p1) < calc(p2)) {
            hi = p2;
        } else {
            lo = p1;
        }
    }

    return calc(lo);
}

int main() {
    read();
    printf("%.9lf\n", work());
    return 0;
}