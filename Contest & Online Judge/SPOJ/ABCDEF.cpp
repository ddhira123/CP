#include <cstdio>
#include <algorithm>
using namespace std;
int cnt,n,arr[105],data[1000005],a,b,c,data2[1000005],cnt2;
long long ans;

int main(){
 scanf("%d",&n);
 for(a=0;a<n;a++)
  scanf("%d",&arr[a]);
 for(a=0;a<n;a++)
  for(b=0;b<n;b++)
   for(c=0;c<n;c++)
    if(arr[a]!=0)
     data[cnt++]=arr[a]*(arr[b]+arr[c]);
 sort(data,data+cnt);
 for(a=0;a<n;a++)
  for(b=0;b<n;b++)
   for(c=0;c<n;c++)
    data2[cnt2++]=arr[a]*arr[b]+arr[c];
 sort(data2,data2+cnt2);
 long long jum=1;
 for(a=1;a<cnt2;a++)
  if(data2[a]!=data2[a-1]){
   ans+=jum*(upper_bound(data,data+cnt,data2[a-1])-lower_bound(data,data+cnt,data2[a-1]));
   jum=1;
  }
  else
   jum++;
 ans+=jum*(upper_bound(data,data+cnt,data2[a-1])-lower_bound(data,data+cnt,data2[a-1]));
 printf("%lld\n",ans);
 return 0;
}