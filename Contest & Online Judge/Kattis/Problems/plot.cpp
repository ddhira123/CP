#include <bits/stdc++.h>
using namespace std;

int n;
long long comb[8][8];
long long c[8];
long long a[8];

long long C(int x,int y){
    if(x < y) return 0;
    if(y == 0) return 1;
    if(comb[x][y]) return comb[x][y];
    return comb[x][y] = C(x - 1,y) + C(x - 1,y - 1);
}

long long f(long long x){
    long long y = 1;
    long long res = 0;
    for(int i = 0 ; i <= n ; i++){
        res += y * a[i];
        y *= x;
    }
    return res;
}

int main(){
    cin >> n;
    for(int i = n ; i >= 0 ; i--)
        cin >> a[i];
    c[0] = f(0);
    for(int i = 1 ; i <= n ; i++){
        long long res = f(i);
        for(int j = 0 ; j < i ; j++)
            res -= C(i,j) * c[j];
        c[i] = res; 
    }
    for(int i = 0 ; i <= n ; i++)
        printf("%lld%c",c[i],i == n ? '\n' : ' ');  
    return 0;
}

