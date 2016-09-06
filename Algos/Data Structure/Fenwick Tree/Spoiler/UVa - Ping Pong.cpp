#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;

const int MAXN = 20005;
const int MAXX = 100000;

int BIT[2][MAXX + 5]; // index 0 untuk kiri, 1 untuk kanan
int n,tc;
int arr[MAXN];

void update(int id,int x,int val){
    for( ; x <= MAXX ; x += x & -x)
        BIT[id][x] += val;
}

int query(int id,int x){
    int res = 0;
        for( ; x > 0 ; x -= x & -x)
            res += BIT[id][x];
    return res;
}

int main(){
    scanf("%d",&tc);

    while(tc--){
        memset(BIT,0,sizeof BIT);
        scanf("%d",&n);

        for(int i = 0 ; i < n ; i++){
            scanf("%d",&arr[i]);
            update(1, arr[i], 1);
        }

        LL ans = 0;
        for(int i = 0 ; i < n ; i++){
            update(1, arr[i], -1);

            int val1 = query(0,arr[i] - 1);
            int val2 = query(0,MAXX) - query(0,arr[i]);

            int val3 = query(1,arr[i] - 1);
            int val4 = query(1,MAXX) - query(1,arr[i]);

            ans += val1 * val4;
            ans += val2 * val3;
            
            update(0, arr[i], 1);
        }

        printf("%lld\n",ans);
    }
 
    return 0;
}
