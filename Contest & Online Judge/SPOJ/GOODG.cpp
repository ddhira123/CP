#include <cstdio>
using namespace std;

typedef long long LL;

const int N = 1000005;

struct line{
    LL m;
    LL c;
    
    line(){}
    
    line(LL a,LL b){
        m = a;
        c = b;
    }
};

int a[N],d[N];
line stek[N];
int sz,n;

bool bad(line l1,line l2,line l3){
    return (l3.c - l1.c) * (l1.m - l2.m) >= (l2.c - l1.c) * (l1.m - l3.m);
}

void Add(line x){
    while(sz >= 2 && bad(stek[sz - 2],stek[sz - 1],x))
        sz--;
    stek[sz++] = x;    
}

LL Query(LL x){
    int lo = 0,hi = sz - 1;
    while(lo < hi){
        int mi = (lo + hi) >> 1;
        if(x * (stek[mi].m - stek[mi + 1].m) >= (stek[mi + 1].c - stek[mi].c))
            hi = mi;
        else
            lo = mi + 1;     
    }
    return x * stek[lo].m + stek[lo].c;
}

int main(){
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; i++)
        scanf("%d %d",&a[i],&d[i]);
    LL ans = 0;    
    Add(line(n + 1,0));
    for(int i = n ; i >= 1 ; i--){
        LL dp = Query(-d[i]);
        dp += (LL)a[i] + (LL)i * (LL)d[i];
        if(dp > ans)
            ans = dp;
        Add(line(i,dp));    
    }    
    printf("%lld\n",ans);
    return 0;
}