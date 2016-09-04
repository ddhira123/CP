#include <cstdio>
using namespace std;

typedef long long LL;

const int N = 100005;
const int K = 12;

struct line{
    LL m;
    LL c;
    
    line(){}
    
    line(LL a,LL b){
        m = a;
        c = b;
    }
};

LL dp[K][N];
line stek[N];
int sz,it;
LL tri[N],sum[N];
int n,k;

bool bad(line l1,line l2,line l3){
    return (l3.c - l1.c) * (l1.m - l2.m) > (l2.c - l1.c) * (l1.m - l3.m);
}

void Add(line x){
    while(sz >= 2 && bad(stek[sz - 2],stek[sz - 1],x))
        sz--;
    stek[sz++] = x;    
}

LL Query(LL x){
    if(it >= sz) it = sz - 1;
    while(it + 1 < sz && stek[it + 1].m * x + stek[it + 1].c <= stek[it].m * x + stek[it].c)
        it++;
    return stek[it].m * x + stek[it].c;    
}

void Init(){
    scanf("%d %d",&n,&k);
    for(int i = 1 ; i <= n ; i++){
        LL a;
        scanf("%lld",&a);
        sum[i] = sum[i - 1] + a;
        tri[i] = tri[i - 1] + a * (LL)i;
    }
}

void Solve(){
    for(int i = n ; i >= 1 ; i--){
        dp[1][i] = sum[i] * (LL)i - tri[i];
        dp[1][i] += (-sum[n]) * (LL)i + tri[n];
    }
    
    for(int i = 2 ; i <= k ; i++){
        sz = 0;
        for(int j = n ; j >= n - i + 1 ; j--){
            dp[i][j] = 0;
            Add(line(-sum[j],tri[j] + dp[i - 1][j + 1]));
        }
        
        for(int j = n - i ; j >= 1 ; j--){
            Add(line(-sum[j],tri[j] + dp[i - 1][j + 1]));
            dp[i][j] = sum[j] * (LL)j - tri[j];
            dp[i][j] += Query(j);
        }
    }
    
    printf("%lld\n",dp[k][1]);
}

int main(){
    Init();
    Solve();
    return 0;
}
