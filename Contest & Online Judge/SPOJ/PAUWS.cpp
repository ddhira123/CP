#include <cstdio>
#include <algorithm>
using namespace std;

int dp[100005],tc,n;
char x[100005];

#define g getchar_unlocked
inline int io(){
 char c;
 while(1){
  c=g();
  if(c!=' '&& c!='\n') break;
 }
 int op=1,ret=0;
 if(c=='-') op=-1;
 else ret=c-'0';
 while(1){
  c=g();
  if(c==' '|| c=='\n'||c==EOF) break;
  ret=(ret<<3)+(ret<<1)+c-'0';
 }
 return ret*op;
}

int main(){
 tc=io();
 while(tc--){
  n=io();
  for(int i=0;i<n;i++)
   x[i]=g();
  dp[n]=0;
  dp[n-1]=1;
  for(int i=n-2;i>=0;i--)
   dp[i]=max(1+dp[i+1],4+dp[i+2]-(x[i]==x[i+1]));
  printf("%d\n",dp[0]);
 }
 return 0;
}
