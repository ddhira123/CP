#include <cstdio>
#include <cstring>
using namespace std;

char x[30];
int dp[30][230],s,tc;

int solve(int pos,int last){
 if(pos==s)
  return 1;
 if(dp[pos][last]!=-1)
  return dp[pos][last];
 int dum=0,res=0;
 for(int i=pos;i<s;i++){
  dum+=(x[i]-'0');
  if(dum>=last)
   res+=solve(i+1,dum);
 }
 return dp[pos][last]=res;
}

int main(){
 scanf("%s",x);
 while(x[0]!='b'){
  s=strlen(x);
  for(int a=0;a<=s;a++)
   for(int b=0;b<=225;b++)
    dp[a][b]=-1;
  printf("%d. %d\n",++tc,solve(0,0));
  scanf("%s",x);
 }
 return 0;
}