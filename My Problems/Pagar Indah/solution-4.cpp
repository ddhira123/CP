#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int arr[N];
int n, k;

long long get_val(int x) {
    return 1ll * x * (x + 1) / 2;
}

void read() {
    scanf("%d %d", &n, &k);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", arr + i);
    }
}

long long solve_zero() {
    long long ret = 0;
    int lst = -1;
    int cur = 0;

    for(int i = 1 ; i <= n ; i++) {
        if(arr[i] != lst) {
            lst = arr[i];
            cur = 1;
        } else {
            cur++;
        }

        ret += cur;
    }

    return ret;
}

long long solve_one() {
    vector<pair<int,int>> v;

    for(int l = 1 ; l <= n ; ) {
        int r = l;
        while(r <= n && arr[l] == arr[r]) {
            r++;
        }
        v.push_back({arr[l], r-l});
        l = r;
    }

    long long ret = solve_zero();
    long long zero = solve_zero();

    for(int i = 0 ; i < v.size() ; i++) {
        if(i-1 >= 0) {
            long long temp = zero;
            temp -= get_val(v[i].second);
            temp -= get_val(v[i-1].second);

            if(v[i].second == 1 && i+1 < v.size() && v[i-1].first == v[i+1].first) {
                temp -= get_val(v[i+1].second);
                temp += get_val(v[i-1].second + 1 + v[i+1].second);
            } else {
                temp += get_val(v[i].second - 1);
                temp += get_val(v[i-1].second + 1);
            }

            ret = max(ret, temp);
        }

        if(i+1 < v.size()) {
            long long temp = zero;

            temp -= get_val(v[i].second);
            temp -= get_val(v[i+1].second);

            temp += get_val(v[i].second - 1);
            temp += get_val(v[i+1].second + 1);

            ret = max(ret, temp);
        }
    }

    return ret;
}

int main() {
    read();
    long long ret = solve_zero();
    if(k == 1) {
        ret = solve_one();
    }
    cout << ret << endl;
    return 0;
}
