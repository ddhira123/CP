#include <bits/stdc++.h>
using namespace std;

const int N = 4005;
const int IMPOSSIBLE = -(1 << 30);

unordered_map<int, int> occ;
int arr[N];
int n;

int calc_top_two() {
    // cout << "mulai top" << endl;

    occ.clear();
    occ.reserve(4096);
    occ.max_load_factor(0.25);

    for(int i = 0 ; i < n ; i++)
        for(int j = i+1 ; j < n ; j++) {
            occ[arr[i] + arr[j]]++;
        }

    int ret = IMPOSSIBLE;

    for(int i = n-1 ; i >= 0 ; i--) {
        for(int j = i-1 ; j >= 0 ; j--) {
            occ[arr[i] + arr[j]]--;
        }
        int start = max(i+1, ret+1);

        for(int j = start ; j < n ; j++) {
            if(occ.count(arr[j] - arr[i]) && occ[arr[j] - arr[i]] > 0) {
                ret = max(ret, j);
            }
            if(occ.count(arr[i] - arr[j]) && occ[arr[i] - arr[j]] > 0) {
                ret = max(ret, i);
            }
        }
    }

    // cout << "selesai top" << endl;
    return ret;
}

int calc_bottom_two() {
    // cout << "mulai bottom" << endl;
    occ.clear();
    occ.reserve(4096);
    occ.max_load_factor(0.25);

    for(int i = 0 ; i < n ; i++)
        for(int j = i+1 ; j < n ; j++) {
            occ[arr[i] + arr[j]]++;
        }

    int ret = IMPOSSIBLE;
    
    for(int i = 0 ; i < n ; i++) {
        for(int j = i+1 ; j < n ; j++) {
            occ[arr[i] + arr[j]]--;
        }

        int en = (ret == IMPOSSIBLE) ? 0 : ret+1;
        for(int j = i-1 ; j >= en ; j--) {
            if(occ.count(arr[i] - arr[j]) && occ[arr[i] - arr[j]] > 0) {
                ret = max(ret, i);
            }
            if(occ.count(arr[j] - arr[i]) && occ[arr[j] - arr[i]] > 0) {
                ret = max(ret, j);
            }
        }
    }

    // cout << "selesai bottom" << endl;

    return ret;   
}

void read() {
    scanf("%d", &n);

    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
    }
}

void prepare() {
    sort(arr, arr + n);
}

int work() {
    int ret = calc_top_two();
    ret = max(ret, calc_bottom_two());

    return ret;
}

int main() {
    read();
    prepare();

    int ret = work();
    if(ret == IMPOSSIBLE) {
        puts("no solution");
    } else {
        printf("%d\n", arr[ret]);
    }
    return 0;
}