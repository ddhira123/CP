#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> prim;
bool flag[46345];
int n,m,tc;
long long ans;

#define g getchar_unlocked

inline int io(){
 register char c;
 while(1){
  c=g();
  if(c!=' ' && c!='\n') break;
 }
  int ret=0,op=1;
  if(c=='-') op=-1;
  else ret=c-'0';
  while(1){
   c=g();
   if(c==' '||c=='\n'||c==EOF) break;
   ret=(ret<<3)+(ret<<1)+c-'0';
  }
  return ret*op;
}

int main(){
 for(int i=2;i<=46340;i++)
  if(!flag[i]){
   prim.push_back(i);
   for(int j=i;j<=46340/i;j++)
    flag[i*j]=1;
  }
 tc=io();
 while(tc--){
  ans=1;
  n=io();m=io();
  for(int i=0;i<prim.size();i++){
   int p1=0,p2=0;
   while(n%prim[i]==0)
    n/=prim[i],p1++;
   while(m%prim[i]==0)
    m/=prim[i],p2++;
   if(p1!=p2){
   int limit=max(p1,p2);//-min(p1,p2);
   for(int j=0;j<limit;j++)
    ans*=(long long)prim[i];
   }
   if(n==1||m==1) break;
  }
  if(n!=m)
   ans*=(long long)n,ans*=(long long)m;
  printf("%lld\n",ans);
 }
 return 0;
}