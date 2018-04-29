#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MAXX = 1e9;

int rand_int(int lmt) {
    return rand() % lmt + 1;
}

int n;
int arr[N];

void read() {
    scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &arr[i]);
    }
}

int work() {
    vector<int> v[2];
    for(int i = 0 ; i < n ; i++) {
        v[i%2].push_back(arr[i]);
    }

    sort(v[0].begin(), v[0].end());
    sort(v[1].begin(), v[1].end());

    vector<int> ar;
    for(int i = 0 ; i < v[0].size() ; i++) {
        ar.push_back(v[0][i]);
        if(i < v[1].size()) {
            ar.push_back(v[1][i]);
        }
    }

    for(int i = 0 ; i+1 < n ; i++) {
        if(ar[i] > ar[i+1]) {
            return i;
        }
    }

    return -1;
}

// int brute() {
//     bool done = false;

//     while(!done) {
//         done = true;
//         for(int i = 0 ; i+2 < n ; i++) {
//             if(arr[i] > arr[i+2]) {
//                 done = false;
//                 swap(arr[i], arr[i+2]);
//             }
//         }
//     }

//     for(int i = 0 ; i+1 < n ; i++) {
//         if(arr[i] > arr[i+1]) {
//             return i;
//         }
//     }

//     return -1;
// }

int main() {
    int t; cin >> t;

    for(int tc = 1 ; tc <= t ; tc++) {
        read();
        int ret = work();

        if (ret == -1) {
            printf("Case #%d: OK\n", tc);
        }
        else {
            printf("Case #%d: %d\n", tc, ret);
        }
    }
    return 0;
}