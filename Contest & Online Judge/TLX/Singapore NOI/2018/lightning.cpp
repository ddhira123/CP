#include <bits/stdc++.h>
using namespace std;

inline int io() {
    register char c;
    c = getchar_unlocked();
    while(c == ' ' || c == '\n') c = getchar_unlocked();
    int ret = c - '0';
    
    while(1) {
        c = getchar_unlocked();
        if(!('0' <= c && c <= '9')) return ret;
        ret = (ret << 3) + (ret << 1) + (c - '0');
    }
}

const int N = 1e7 + 5;

pair<int, int> arr[N];
pair<int, int> temp[N];
int n;

void read() {
    // scanf("%d", &n);
    n = io();
    int sz = 0;

    for(int i = 0 ; i < n ; i++) {
        int x, y;
        // scanf("%d %d", &x, &y);
        x = io(); y = io();

        if(sz > 0 && arr[sz-1].first == x) {
            arr[sz-1].second = max(arr[sz-1].second, y);
        } else {
            arr[sz++] = {x, y};
        }
    }

    n = sz;
}

void stack_resolve() {
    int t_sz = 0;

    for(int i = 0 ; i < n ; i++) {
        pair<int, int> it = arr[i];

        while(t_sz > 0 && abs(temp[t_sz-1].first - it.first) <= it.second - temp[t_sz-1].second) {
            t_sz--;
        }

        temp[t_sz++] = it;
    }

    n = t_sz;
    for(int i = 0 ; i < n ; i++) {
        arr[i] = temp[i];
    }
}

int work() {
    stack_resolve();
    reverse(arr, arr + n);
    stack_resolve();

    return n;
}

int main() {
    read();
    printf("%d\n", work());
    return 0;
}