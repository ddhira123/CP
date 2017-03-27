#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL n,m;
LL base[2][2];
LL ans[2][2];
int tc;

inline LL add(LL &a,LL b){
    a += b;
    if(a >= m) a -= m;
}

//taken from internet
inline LL multiply(LL a,LL b){
    long double res = a;
    res *= b;
    LL c = (LL)(res / m);
    a *= b;
    a -= c * m;
    a %= m;
    if (a < 0)
        a += m;
    return a;    
}

//taken from comment on one of kien_coi_1997 blog in CF
inline void fibo(LL k,LL &x,LL &y){
    if(k == 1){
        x = y = 1;
        return;
    }
    
    if(k & 1){
        fibo(k - 1,y,x);
        y = (y + x);
        if(y >= m) y -= m;
    }
    else{
        LL a,b;
        fibo(k >> 1,a,b);
        
        LL temp = multiply(a,a);
        add(temp,multiply(b,b));
        y = temp;
        
        LL temp2 = b;
        add(temp2,b);
        if(temp2 >= a)
            temp2 -= a;
        else
            temp2 = temp2 + m - a;
        temp = 0;         
        if(temp2 > a) swap(temp2,a);
        add(temp,multiply(a,temp2));
        x = temp;
    }
}

int main(){
    scanf("%d",&tc);
    while(tc--){
        scanf("%lld %lld",&n,&m);
        LL ans = 0;
        if(m > 1){
            LL y;
            fibo(n + 2,ans,y);
            if(ans == 0) ans += (m - 1);
            else ans--;
        }    
        if(ans < (n % m))
            ans = (ans + m) - ((n % m));
        else
            ans = ans - (n % m);    
        printf("%lld\n",ans);    
    }
    return 0;
}