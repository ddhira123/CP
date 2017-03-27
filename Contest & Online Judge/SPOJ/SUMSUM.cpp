#include <cstdio>
using namespace std;

int bit[100005][28],n,q,arr[100005],ret[28],a,b,op;
char z[5];

inline void update(int pos,int bits,int val){
 for(int i=pos;i<=n;i+=i&-i)
  bit[i][bits]+=val;
}

inline void upbit(int pos,int val){
 for(int i=0;i<28;i++)
  if(arr[pos]&(1<<i))
   update(pos,i,-1);
 arr[pos]=val;
 for(int i=0;i<28;i++)
  if(arr[pos]&(1<<i))
   update(pos,i,1);
}

inline void query(int l,int r){
 for(int i=0;i<28;i++) ret[i]=0;
 for(int i=r;i;i-=i&-i)
  for(int j=0;j<28;j++)
   ret[j]+=bit[i][j];
 for(int i=l-1;i;i-=i&-i)
  for(int j=0;j<28;j++)
   ret[j]-=bit[i][j];
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


int main(){
 n=io(); q=io();
 for(int i=1;i<=n;i++)
   a=io(),upbit(i,a);
 while(q--){
  op=io();
  if(op==1){
   a=io(); b=io();
   upbit(b,a);
  }
  else{
   scanf("%s",z);
   a=io(); b=io();
   query(a,b);
   long long ans=0,sum;
   if(z[0]=='A')
    for(int i=0;i<28;i++){
     sum=(long long)ret[i]*(long long)(ret[i]-1)/2LL;
     ans+=sum*(1LL<<i);
    }
   else if(z[0]=='X')
    for(int i=0;i<28;i++){
     sum=(long long)ret[i]*(long long)(b-a+1-ret[i]);
     ans+=sum*(1LL<<i);
    }
   else
    for(int i=0;i<28;i++){
     sum=(long long)ret[i]*(long long)(ret[i]-1)/2LL;
     sum+=(long long)ret[i]*(long long)(b-a+1-ret[i]);
     ans+=sum*(1LL<<i);
    }
    printf("%lld\n",ans);
  }
 }
 return 0;
}
