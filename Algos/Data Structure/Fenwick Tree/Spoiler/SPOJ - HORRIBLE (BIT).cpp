#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;

const int MAXN = 100005;

LL BIT[2][MAXN];// 0 untuk m, 1 untuk c
int n,q,tc;

void update(int id,int x,LL val){
    for(; x <= n ; x += x & -x)
        BIT[id][x] += val;
}

LL query(int x){
    LL m = 0,c = 0;
    for(int i = x ; i > 0 ; i -= i & -i){
        m += BIT[0][i];
        c += BIT[1][i];
    }
    return m * x - c;
}

int main(){
    scanf("%d",&tc);
    
    while(tc--){
        scanf("%d %d",&n,&q);
        memset(BIT,0,sizeof BIT);

        while(q--){
            int a,b,op;
            LL v;
            scanf("%d",&op);
            if(op == 0){
                scanf("%d %d %lld",&a,&b,&v);

                update(0,a,v);
                update(0,b + 1, -v);

                update(1,a,v * (a - 1));
                update(1,b+1,-v * (a - 1));
                update(1,b+1,-v * (b - a + 1)); // sebenarnya bisa digabung dengan di atas
                                                // tapi tidak untuk memperjelas
            }
            else{
                scanf("%d %d",&a,&b);
                printf("%lld\n",query(b) - query(a - 1));
            }
        }
    }
    return 0;
}
