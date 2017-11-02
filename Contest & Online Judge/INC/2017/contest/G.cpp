#include <bits/stdc++.h>
using namespace std;

const int MAX_VAL = 100000;

int mins[MAX_VAL+5];
int n;

int main() {
    scanf("%d", &n);
    for(int i = 0 ; i <= MAX_VAL ; i++) {
        mins[i] = MAX_VAL;
    }

    int ret = -1;
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++) {
            int x; scanf("%d", &x);

            if(mins[x] <= j) {
                ret = max(ret, x);
            }

            mins[x] = min(mins[x], j);
        }

    printf("%d\n", ret);
    return 0;
}