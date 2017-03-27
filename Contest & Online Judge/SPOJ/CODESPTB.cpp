#include <cstdio>
#include <cstring>
using namespace std;

typedef long long LL;

const int MAXN = 100005;
const int MAXX = 1000000;

int BIT[MAXX + 5];
int arr[MAXN];
int tc,n;

void Update(int x){
 for( ; x <= MAXX ; x += x & -x)
    BIT[x]++;
}

int Query(int x){
 int res = 0;
 for( ; x > 0 ; x -= x & -x)
    res += BIT[x];
 return res;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
    memset(BIT,0,sizeof BIT);
    scanf("%d",&n);
    LL ans = 0;
    for(int i = 0 ; i < n ; i++){
        scanf("%d",&arr[i]);
        ans += (i - Query(arr[i]));
        Update(arr[i]);
    }
    printf("%lld\n",ans);
 }
 return 0;
}
