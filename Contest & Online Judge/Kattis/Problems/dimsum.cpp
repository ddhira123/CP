#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
const int MOD = 1e9 + 9;

int n;
vector<int> v[N];
vector<pair<int, int>> arr;

int pwr[N];

void read() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        int x; scanf("%d", &x);

        for(int j = 0 ; j < x;  j++) {
            int y; scanf("%d", &y);

            v[i].push_back(y-1);
        }
    }
}

void prepare() {
    pwr[0] = 1;
    pwr[1] = 2;

    for(int i = 2 ; i < N ; i++) {
        pwr[i] = 1ll * pwr[i-1] * pwr[1] % MOD;
    }

    for(int i = 0 ; i < n ; i++) {
        for(int x : v[i]) {
            int cw = x - i;
            if(cw < 0) cw += n;
            int ccw = n - cw;
            if(ccw == n) ccw = 0;

            arr.push_back({cw, ccw});
        }
    }
}

int calc_cw() {
    vector<pair<int, int>> data = arr;
    sort(data.begin(), data.end());

    int ret = 0;
    int all_one = 0;
    int all_zero = 0;

    priority_queue<int> pq;

    for(auto it : data) {
        int cw = it.first;
        int ccw = it.second;

        while(!pq.empty() && -pq.top() < cw) {
            pq.pop();

            all_one--;
            all_zero++;
        }

        if(ccw >= cw) {
            int subset = pwr[all_one + all_zero];

            ret = (ret + 1ll * cw * subset) % MOD;
        } else {
            int subset = pwr[all_one + all_zero];
            subset = (subset + MOD - pwr[all_zero]) % MOD;

            ret = (ret + 1ll * cw * subset) % MOD;
        }

        all_one++;

        pq.push(-ccw);
    }

    return ret;
}

int calc_ccw() {
    vector<pair<int, int>> data = arr;
    for(auto &x : data) {
        swap(x.first, x.second);
    }
    sort(data.begin(), data.end());

    int ret = 0;
    int all_one = 0;
    int all_zero = 0;

    priority_queue<int> pq;

    for(auto it : data) {
        int ccw = it.first;
        int cw = it.second;

        while(!pq.empty() && -pq.top() <= ccw) {
            pq.pop();

            all_one--;
            all_zero++;
        }

        if(cw > ccw) {
            int subset = pwr[all_one + all_zero];

            ret = (ret + 1ll * ccw * subset) % MOD;
        } else {
            int subset = pwr[all_one + all_zero];
            subset = (subset + MOD - pwr[all_zero]) % MOD;

            ret = (ret + 1ll * ccw * subset) % MOD;
        }

        all_one++;

        pq.push(-cw);
    }

    return ret;
}

int main() {
    read();
    prepare();

    int ret = calc_cw() + calc_ccw();
    ret %= MOD;

    printf("%d\n", ret);
    return 0;
}