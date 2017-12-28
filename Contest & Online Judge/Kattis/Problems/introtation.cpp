#include <bits/stdc++.h>
using namespace std;

int minimum_rotation(int x) {
    int bagi = 1;
    while(bagi * 10 <= x) {
        bagi *= 10;
    }

    int mins = x;

    for(int i = 1 ; i <= bagi ; i *= 10) {
        int atas = x / i;
        int bawah = x % i;

        // printf("x %d i %d atas %d bawah %d\n", x, i, atas, bawah);

        bawah *= (bagi * 10 / i);

        int cur = atas + bawah;
        if(cur >= bagi)
            mins = min(mins, cur);
    }

    return mins;
}

const int MX = 1e6 + 5;

int min_rot[MX];
int cnt[MX];

void init() {
    for(int i = 1 ; i < MX ; i++)
        min_rot[i] = minimum_rotation(i);
}

long long solve(int a, int b) {
    long long ret = 0;

    for(int i = a ; i <= b ; i++) {
        ret += cnt[min_rot[i]];
        cnt[min_rot[i]]++;
    }

    for(int i = a ; i <= b ; i++) {
        cnt[min_rot[i]] = 0;
    }

    return ret;
}

int main() {
    init();

    int t; cin >> t;
    for(int tc = 1 ; tc <= t ; tc++) {
        int a, b;
        cin >> a >> b;
        cout << solve(a, b) << endl;
    }
    return 0;
}

