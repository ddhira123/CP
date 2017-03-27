#include <cstdio>
#include <algorithm>
using namespace std;

int prefix[35],sum[35][35],ret,r,c;
char x[35];

int main(){
 scanf("%d %d",&r,&c);
 for(int i=0;i<r;i++){
  scanf("%s",x);
  for(int j=1;j<=c;j++)
   prefix[j]=prefix[j-1]+(x[j-1]=='H' ? 1 : -1);
  for(int j=1;j<=c;j++)
   for(int k=j;k<=c;k++){
    sum[j][k]=(abs(prefix[k]-prefix[j-1])==k-j+1 ? sum[j][k]+1 : 0);
    if(sum[j][k]==k-j+1) ret=max(ret,sum[j][k]*sum[j][k]);
   }
 }
 printf("%d\n",ret);
 return 0;
}