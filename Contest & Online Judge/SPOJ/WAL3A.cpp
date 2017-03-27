#include <cstdio>
#include <algorithm>
using namespace std;

int arr[100005],tc,n;
long long ans;

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
  ans=0;
  int tmp;
  n=io();
  for(int i=0;i<n;i++)
   arr[i]=io();
  for(int i=0;i<n;i++){
   tmp=0;
   if(i>0) tmp=max(tmp,arr[i-1]);
   if(i<n-1) tmp=max(tmp,arr[i+1]);
   ans+=(long long)min(tmp,arr[i]);
  }
  printf("%lld\n",ans);
 }
 return 0;
}