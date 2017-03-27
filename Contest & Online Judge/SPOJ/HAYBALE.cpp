#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;

int n,q;
int arr[MAXN];
int BIT[MAXN];

void Update(int x,int val){
 for(; x <= n ; x += x & -x)
    BIT[x] += val;
}

int Query(int x){
 int res = 0;
 for(; x > 0 ; x -= x & -x)
    res += BIT[x];
 return res;
}

int main(){
 scanf("%d %d",&n,&q);
 while(q--){
    int a,b;
    scanf("%d %d",&a,&b);
    Update(a, 1);
    Update(b + 1, -1);
 }
 for(int i = 1 ; i <= n ; i++)
    arr[i] = Query(i);
 sort(arr + 1, arr + n + 1);
 printf("%d\n",arr[(n + 1)/2]);
 return 0;
}
