#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

char c[85];
int dp[85][85];
int len;

int solve(int l,int r){
 if(dp[l][r]!=-1) return dp[l][r];
 int ret=r-l+1;
 for(int i=l;i<r;i++){
  int hm=solve(l,i);
  int it1=0,it2=i+1;
  while(1){
   if(it1==0) ret=min(ret,hm+solve(it2,r));
   if(it2>r) break;
   if(c[it1+l]!=c[it2]) break;
   it1=(it1+1)%(i-l+1);
   it2++;
  }
 }
 return dp[l][r]=ret;
}

int main(){
 scanf("%s",c);
 while(c[0]!='*'){
  len=strlen(c);
  for(int i=0;i<=len;i++)
   for(int j=0;j<=len;j++)
    dp[i][j]=-1;
  for(int i=0;i<=len;i++)
   dp[i][i]=1,dp[i+1][i]=0; 
  printf("%d\n",solve(0,len-1));  
  scanf("%s",c);
 }
 return 0;
}
