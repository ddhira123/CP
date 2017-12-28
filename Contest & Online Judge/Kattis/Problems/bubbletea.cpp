#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int tea[N];
int topping[N];
int n, m, k;

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; i++) {
        scanf("%d", &tea[i]);
    }
    scanf("%d", &m);
    for(int i = 1 ; i <= m ; i++) {
        scanf("%d", &topping[i]);
    }

    int mins = 2e9;
    for(int i = 1 ; i <= n ; i++) {
        int x; scanf("%d", &x);

        for(int j = 1 ; j <= x ; j++) {
            int paired;
            scanf("%d", &paired);

            mins = min(mins, tea[i] + topping[paired]);
        }
    }

    scanf("%d", &k);

    printf("%d\n", max(0, k / mins - 1));
    return 0;
}

