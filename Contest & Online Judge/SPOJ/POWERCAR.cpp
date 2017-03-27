#include <cstdio>
#include <algorithm>
using namespace std;
#define INF 1000000000
int dp[2][1001][1001],tc,n,x;
char y[1005];

int solve(int op,int pos,int left){
 if(left==-1 || pos==n) return INF;
 if(op==0 && pos==n-1) return 0;
 if(dp[op][pos][left]!=-1) return dp[op][pos][left];
 if(op==0)
  return dp[op][pos][left]=min(4+solve(1,pos+1,left),1+solve(0,pos+1,left-(y[pos+1]=='#')));
 else
  return dp[op][pos][left]=2+min(solve(1,pos+1,left),(y[pos]!='#' ? solve(0,pos,left) : INF));
}

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

inline void getstr(){
 int i=0;
 char z;
 while(1){
  z=g();
  if(z=='\n'||z==EOF) break;
  y[i++]=z;
 }
}

int main(){
 tc=io();
 while(tc--){
  n=io(); x=io();
  getstr();
  for(int i=0;i<2;i++)
   for(int j=0;j<n;j++)
    for(int k=0;k<=x;k++)
     dp[i][j][k]=-1;
  printf("%d\n",solve(0,0,x));
 }
 return 0;
}