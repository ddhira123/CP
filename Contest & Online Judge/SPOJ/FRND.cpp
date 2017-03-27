#include <cstdio>
using namespace std;

bool tmp[25];
int n,now,a,cnt;
long long ans,sum[25],pan[25];

int main(){
 scanf("%d",&n);
 pan[0]=1;
 for(a=1;a<20;a++){
  pan[a]=pan[a-1]<<1;
  //printf("%d -> %lld\n",a,pan[a]);
 }
 for(int b=0;b<n;b++){
  scanf("%d",&now);
  for(a=0;a<20;a++)
   tmp[a]=0;
  cnt=0;
  while(now){
   if(now&1)
    tmp[cnt]=1;
   cnt++;
   now>>=1;
  }
  for(a=0;a<20;a++){
   if(!tmp[a])
    ans+=pan[a]*sum[a];
   else
    ans+=pan[a]*(b-sum[a]);
   //printf("%d %lld\n",a,ans);
   sum[a]+=tmp[a];
  }
 }
 printf("%lld\n",ans);
 return 0;
}
