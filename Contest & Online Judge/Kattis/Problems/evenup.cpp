#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int stek[N];
int n;
int sz;

int main(){
    scanf("%d",&n);
    for(int i = 0 ; i < n ; i++){
        int x;
        scanf("%d",&x);
        if(sz > 0 && (stek[sz - 1] + x) % 2 == 0)
            sz--;
        else
            stek[sz++] = x; 
    }
    printf("%d\n",sz);
    return 0;
}
