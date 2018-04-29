#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int LMT = 1e9;

vector<pair<LL, LL>> fibo;
vector<pair<LL, LL>> sols;

void precompute() {
    fibo.push_back({1, 0});
    fibo.push_back({0, 1});
    sols = fibo;

    for(int i = 2 ; ; i++) {
        LL a = fibo[i-1].first + fibo[i-2].first;
        LL b = fibo[i-1].second + fibo[i-2].second;

        if(a + b > LMT) {
            break;
        }

        fibo.push_back({a, b});

        LL x = sols[i-1].second - sols[i-1].first;
        LL y = sols[i-1].first;

        sols.push_back({x, y});
    }
}

void work(LL n) {
    pair<LL, LL> ans = {LMT, LMT};

    for(int i = 2 ; i < fibo.size() ; i++) {
        LL a = fibo[i].first;
        LL b = fibo[i].second;

        LL x = n * sols[i].first;
        LL y = n * sols[i].second;

        int sign = x < y ? 1 : -1;
        LL lo = 0, hi = LMT;

        if(sign == 1) {
            while(lo < hi) {
                LL mid = (lo + hi + 1) / 2;

                LL xx = x + b * mid * sign;
                LL yy = y - a * mid * sign;

                if(xx <= yy) {
                    lo = mid;
                } else {
                    hi = mid - 1;
                }
            }
        } else {
            while(lo < hi) {
                LL mid = (lo + hi) / 2;

                LL xx = x + b * mid * sign;
                LL yy = y - a * mid * sign;

                if(xx <= yy) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }
        }

        x = x + b * lo * sign;
        y = y - a * lo * sign;

        if(x <= y && x > 0) {
            if(y < ans.second || (y == ans.second && x < ans.first)) {
                ans = {x, y};
            }
        }
    }

    printf("%lld %lld\n", ans.first, ans.second);
}

int main() {
    precompute();
    int t; cin >> t;

    for(int tc = 1 ; tc <= t ; tc++) {
        int n; cin >> n;
        work(n);
    }
    return 0;
}
