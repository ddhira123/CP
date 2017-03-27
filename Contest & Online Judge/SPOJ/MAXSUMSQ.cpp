#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;
typedef long long LL;

map<int,int> m;
int sum,ans,tc,arr[100005],n;
LL res;

#define g getchar_unlocked
inline int io(){
char c;
while(1){
c=g();
if(c!=' ' && c!='\n')
break;
}
int res=0; bool min=0;
if(c=='-')min=1;
else res=c-'0';
while(1){
c=g();
if(c==' ' || c=='\n' || c==EOF)
break;
res=(res<<1)+(res<<3)+(c-'0');
}
if(min)res*=-1; return res;
}

int main(){
 tc=io();
 while(tc--){
  sum=res=0;
  m.clear();
  m[0]++;
  ans=-1000000000;
  n=io();
  for(int i=0;i<n;i++){
   arr[i]=io();
   sum+=arr[i];
   ans=max(ans,sum);
   if(sum<0) sum=0;
  }
  sum=0;
  for(int i=0;i<n;i++){
   sum+=arr[i];
   res+=(LL) m[sum-ans];
   m[sum]++;
  }
  printf("%d %lld\n",ans,res);
 }
 return 0;
}

