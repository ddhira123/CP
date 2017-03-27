#include <cstdio>
using namespace std;

int prim[10000005],tc,n,jum[3];

int main(){
 for(int i=2;i<=10000000;i++)
  if(prim[i]==0)
   for(int j=1;j<=10000000/i;j++)
    if(prim[i*j]==0)
     prim[i*j]=i;
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  int cnt=1,last=0;
  jum[0]=jum[1]=0;
  while(n>1){
   if(prim[n]==last)
    cnt++;
   else{
    jum[cnt&1]++;
    last=prim[n];
    cnt=1;
   }
   n/=prim[n];
  }
  jum[cnt&1]++;
  jum[1]--;
  //printf("%d %d\n",jum[0],jum[1]);
  if(jum[0]<=jum[1])
   printf("Ordinary Number\n");
  else
   printf("Psycho Number\n");
 }
 return 0;
}