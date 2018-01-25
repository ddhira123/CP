#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int arr[N];
int psum[N];
int min_prefix[N];
int min_suffix[N];
int n;

bool read() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &arr[i]);
    }

    return n > 0;
}

void prepare() {
    for(int i = 1 ; i <= n ; i++) {
        psum[i] = arr[i] + psum[i-1];
    }

    min_prefix[1] = psum[1];
    for(int i = 2 ; i <= n ; i++) {
        min_prefix[i] = min(min_prefix[i-1], psum[i]);
    }

    min_suffix[n] = psum[n];
    for(int i = n-1 ; i >= 1 ; i--) {
        min_suffix[i] = min(min_suffix[i+1], psum[i]);
    }
}

bool check(int i) {
    int min_suf = min_suffix[i];
    if(min_suf- psum[i-1] < 0) {
        return false;
    }

    if(i > 1) {
        int min_pref = min_prefix[i-1];
        if(min_pref - psum[i-1] + psum[n] < 0) {
            return false;
        }
    }

    return true;
}

int work() {
    int ret = 0;
    for(int i = 1 ; i <= n ; i++) {
        ret += check(i);
    }
    return ret;
}

int main() {
    while(read()) {
        prepare();
        printf("%d\n", work());
    }
    return 0;
}