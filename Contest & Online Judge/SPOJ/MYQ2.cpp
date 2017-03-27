#include <cstdio>
#include <cstring>
using namespace std;

int idx,sum,last[1000010],mod,k,tc,maks,len;
char x[1000005];

const int INF=1000000000;

inline int trans(char z){
 int ret=0;
 if('a'<=z && z<='z') ret=z-'a'+1;
 else if('A'<=z && z<='Z') ret=z-'A'+51;
 else if(z==' ') ret=32;
 return ret;
}

#define g getchar//_unlocked
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
 char c;
 while(1){
  c=g();
  if(c=='\n') break;
  x[i++]=c;
 }
 len=i;
}

int main(){
 tc=io();
 while(tc--){
  getstr();
  mod=io(); k=io();
  for(int i=1;i<mod;i++)
   last[i]=INF;
  last[0]=-1;
  sum=0; maks=-1;
  for(int i=0;i<len;i++){
   sum+=trans(x[i]);
   while(sum>=mod) sum-=mod;
   int hm=sum-k;
   if(hm<0) hm+=mod;
   if(i-last[hm]>maks)
    maks=i-last[hm],idx=last[hm]+1;
   last[sum]=(last[sum]==INF ? i : last[sum]);
  }
  if(maks==-1) puts("-1");
  else printf("%d %d\n",idx,maks);
 }
 return 0;
}
