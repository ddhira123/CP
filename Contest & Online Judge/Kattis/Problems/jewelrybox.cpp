#include <bits/stdc++.h>
using namespace std;

double calc(double x, double y, double h) {
    double a = x - 2 * h;
    double b = y - 2 * h;

    return a * b * h;
}

double solve(double x, double y) {
    double lo = 0;
    double hi = min(x, y) / 2;

    for(int i = 0 ; i < 50 ; i++) {
        double p1 = lo + (hi - lo) / 3;
        double p2 = lo + 2 * (hi - lo) / 3;

        if(calc(x, y, p1) < calc(x, y, p2)) {
            lo = p1;
        } else {
            hi = p2;
        }
    }

    return calc(x, y, lo);
}

int main() {
    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        double x, y;
        cin >> x >> y;
        printf("%.13lf\n", solve(x, y));
    }
    return 0;
}

