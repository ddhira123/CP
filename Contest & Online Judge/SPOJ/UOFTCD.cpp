#include <cstdio>
#include <algorithm>
using namespace std;

int d,m,h,l,tc,sum,scare,T[105],F[105],ans;
bool flag[105];

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d %d %d",&d,&m,&h,&l);
  T[m+1]=d;
  F[m+1]=0;
  for(int i=1;i<=m;i++)
   scanf("%d %d",&T[i],&F[i]);
  ans=1000000000;
  for(int i=1;i<=m+1;i++){
   flag[i]=1;
   scare=sum=0;
   for(int j=1;j<=m+1;j++){
    if(scare>=l) break;
    else if(scare>=h) sum+=T[j]-T[j-1];
    if(!flag[j]) scare+=F[j];
    if(scare<0) scare=0;
   }
   flag[i]=0;
   ans=min(ans,sum);
  }
  printf("%d\n",ans);
 }
 return 0;
}
