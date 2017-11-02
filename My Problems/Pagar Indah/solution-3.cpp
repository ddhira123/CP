#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int arr[N];
int n, k;

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
    long long ret = 0;

    for(int i = 1 ; i <= n ; i++) {
        for(int j = i-1 ; j <= i+1 ; j++)
            if(j >= 1 && j <= n) {
                int temp = arr[i];
                arr[i] = arr[j];

                ret = max(ret, solve_zero());

                arr[i] = temp;
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
