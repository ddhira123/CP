#include <cstdio>
#include <cstring>
using namespace std;

int dp[25],s;
char x[25];

int solve(int pos){
 if(dp[pos]!=-1)
  return dp[pos];
 if(x[pos]=='0')
  return dp[pos]=solve(pos+1);
 dp[pos]=0;
 int dum=x[pos]-'0';
 for(int i=pos+1;i<=s&&dum<=20;i++){
  dp[pos]+=solve(i);
  dum*=10;
  dum+=x[i]-'0';
 }
 return dp[pos];
}

int main(){
 scanf("%s",x);
 s=strlen(x);
 for(int a=0;a<s;a++)
  dp[a]=-1;
 dp[s]=1;
 printf("%d\n",solve(0));
 return 0;
}
