#include <cstdio>
using namespace std;
typedef long long LL;

struct hm{
 LL start,end,inc,sum;
}stree[400005];

LL jum(LL st,LL en,LL l,LL r){
 return (en+st)*(r-l+1)/2LL;
}

void propagate(int id,LL l,LL r){
 if(stree[id].inc){
  int chld=id<<1;
  LL m=(l+r)>>1,mi=stree[id].start+stree[id].inc*(m-l);
  stree[chld+1].inc+=stree[id].inc;
  stree[chld+2].inc+=stree[id].inc;
  stree[chld+1].start+=stree[id].start;
  stree[chld+1].end+=mi;
  stree[chld+2].start+=mi+stree[id].inc;
  stree[chld+2].end+=stree[id].end;
  stree[chld+1].sum+=jum(stree[id].start,mi,l,m);
  stree[chld+2].sum+=jum(mi+stree[id].inc,stree[id].end,m+1,r);
  stree[id].inc=stree[id].start=stree[id].end=0;
 }
}

void update(int id,int l,int r,int x,int y){
 if(x<=l && r<=y){
  stree[id].inc++;
  stree[id].start+=(LL)(l-x+1);
  stree[id].end+=(LL)(r-x+1);
  stree[id].sum+=jum(l-x+1,r-x+1,l,r);
 }
 else{
  int m=(l+r)>>1,chld=id<<1;
  propagate(id,l,r);
  if(x<=m) update(chld+1,l,m,x,y);
  if(y>m)  update(chld+2,m+1,r,x,y);
  stree[id].sum=stree[chld+1].sum+stree[chld+2].sum;
 }
}

LL query(int id,int l,int r,int x,int y){
 if(x<=l && r<=y)
  return stree[id].sum;
 else{
  int m=(l+r)>>1,chld=id<<1;
  LL ret=0;
  propagate(id,l,r);
  stree[id].sum=stree[chld+1].sum+stree[chld+2].sum;
  if(x<=m) ret+=query(chld+1,l,m,x,y);
  if(y>m)  ret+=query(chld+2,m+1,r,x,y);
  return ret;
 }
}

int n,q,a,b,op;

int main(){
 scanf("%d %d",&n,&q);
 while(q--){
  scanf("%d %d %d",&op,&a,&b);
  if(op)
   printf("%lld\n",query(0,1,n,a,b));
  else
   update(0,1,n,a,b);
 }
 return 0;
}
