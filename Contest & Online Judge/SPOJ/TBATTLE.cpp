#include <cstdio>
using namespace std;

int l,prim[10],arr[100005],jum[10],acc[10],siz,tmp[10],ansl,ansr,n;

void proc(int yee,int op){
 for(int i=0;i<siz;i++)
  while(yee%prim[i]==0)
   yee/=prim[i],acc[i]+=op;
}


bool valid(int yee){
 for(int i=0;i<siz;i++){
  tmp[i]=0;
  while(yee%prim[i]==0)
   yee/=prim[i],tmp[i]++;
  if(acc[i]-tmp[i]<jum[i])
   return 0;
 }
 return 1;
}

#define g getchar_unlocked

inline int io(){
 char c;
 while(1){
  c=g();
  if(c!=' '|| c!='\n') break;
 }
 int res,min=1;
 if(c=='-') min=-1;
 else res+=c-'0';
 while(1){
  c=g();
  if(c==' '||c=='\n'||c==EOF) break;
  res=(res<<3)+(res<<1)+c-'0';
 }
 return res*min;
}

int main(){
 n=io();
 int dum=n;
 for(int i=2;i<=n&&dum>1;i++)
  if(dum%i==0){
   prim[siz]=i;
   while(dum%i==0)
    dum/=i,jum[siz]++;
   siz++;
  }
 ansr=1000000000;
 for(int r=0;r<n;r++){
  arr[r]=io();
  proc(arr[r],1);
  while(valid(arr[l]))
   proc(arr[l],-1),l++;
  if(valid(1)&&ansr-ansl+1>r-l+1)
   ansr=r,ansl=l;
 }
 if(ansr==1000000000) puts("-1");
 else printf("%d %d\n",ansl,ansr);
 return 0;
}