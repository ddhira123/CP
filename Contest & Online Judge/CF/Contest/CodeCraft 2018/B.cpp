#include <bits/stdc++.h>
using namespace std;

map<int, int> cnt;
int n;

int main() {
    int n; scanf("%d", &n);
    for(int i = 0 ; i < n ; i++) {
        int x; scanf("%d", &x);
        cnt[x]++;
    }
    for(auto x : cnt) {
        if(x.second & 1) {
            puts("Conan");
            return 0;
        }
    }
    puts("Agasa");
    return 0;
}