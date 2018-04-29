#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int n;
vector<string> arr[4];

void read() {
    cin >> n;
    for(int i = 0 ; i < 4 ; i++) {
        arr[i].resize(n);
        for(int j = 0 ; j < n ; j++) {
            cin >> arr[i][j];
        }
    }
}

int check(int rs, int cs, vector<string> v) {
    int ret = 0;

    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++) {
            int parity = (rs + cs + i + j) % 2;
            int cur = v[i][j] - '0';

            ret += (parity != cur);
        }
    }

    return ret;
}

int work() {
    vector<int> rs = {0, n, 0, n};
    vector<int> cs = {0, 0, n, n};

    vector<int> order = {0, 1, 2, 3};
    int ret = 1e9;

    do {
        int val = 0;
        for(int i = 0 ; i < 4 ; i++) {
            val += check(rs[i], cs[i], arr[order[i]]);
        }

        ret = min(ret, val);
    } while(next_permutation(order.begin(), order.end()));

    return ret;
}

int main() {
    read();
    printf("%d\n", work());
    return 0;
}