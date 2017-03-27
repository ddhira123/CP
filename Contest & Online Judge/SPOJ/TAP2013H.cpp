#include <algorithm>
#include <cstdio>
using namespace std;

int dp[1000005],fak[1000005],prefix[1000005][15],tc,p,q,k;
bool flag[1000005];

int solve(int n){
 if(dp[n]!=0)
  return dp[n];
 if(n==fak[n])
  return dp[n]=1;
 return dp[n]=1+solve(fak[n]);
}

int main(){
 for(int a=2;a<=1000000;a++)
  if(!flag[a]){
   fak[a]=a;
   for(int b=2;b<=1000000/a;b++){
    flag[a*b]=1;
    fak[a*b]+=a;
   }
  }
 for(int a=2;a<=1000000;a++){
  for(int b=0;b<=12;b++)
   prefix[a][b]=prefix[a-1][b];
  prefix[a][solve(a)]++;
 }
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d %d",&p,&q,&k);
  if(k<=12)
   printf("%d\n",prefix[q][k]-prefix[p-1][k]);
  else
   printf("0\n");
 }
 return 0;
}