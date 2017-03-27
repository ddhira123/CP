#include <cstdio>
#include <algorithm>
using namespace std;
struct tree{
 long long sum;
 int mins;
} seg[500005];

int arr[100005],n,q,a,b;
char x[10];

void build(int id,int l,int r){
 if(l==r)
  seg[id]=(tree){arr[l],arr[l]};
 else{
  int m=(l+r)>>1,chld=id<<1;
  build(chld+1,l,m);
  build(chld+2,m+1,r);
  seg[id]=(tree){seg[chld+1].sum+seg[chld+2].sum,min(seg[chld+1].mins,seg[chld+2].mins)};
 }
}

void update(int id,int l,int r,int x,int val){
 if(l==r){
  seg[id].sum+=val;
  seg[id].mins=seg[id].sum;
 }
 else{
  int m=(l+r)>>1,chld=id<<1;
  if(x<=m)
   update(chld+1,l,m,x,val);
  else
   update(chld+2,m+1,r,x,val);
  seg[id]=(tree){seg[chld+1].sum+seg[chld+2].sum,min(seg[chld+1].mins,seg[chld+2].mins)};
 }
}

tree query(int id,int l,int r,int x,int y){
 if(x<=l && r<=y)
  return seg[id];
 else{
  int m=(l+r)>>1,chld=id<<1;
  tree tmp=(tree){0LL,1000000001};
  if(x<=m){
   tree res=query(chld+1,l,m,x,y);
   tmp.sum+=res.sum;
   tmp.mins=min(tmp.mins,res.mins);
  }
  if(y>m){
   tree res=query(chld+2,m+1,r,x,y);
   tmp.sum+=res.sum;
   tmp.mins=min(tmp.mins,res.mins);
  }
  return tmp;
 }
}

int main(){
 scanf("%d",&n);
 for(int i=0;i<n;i++)
  scanf("%d",&arr[i]);
 build(0,0,n-1);
 scanf("%d",&q);
 while(q--){
  scanf("%s %d %d",x,&a,&b);
  if(x[0]=='G')
   update(0,0,n-1,b,a);
  else if(x[0]=='E')
   update(0,0,n-1,b,-a);
  else{
   tree res=query(0,0,n-1,a,b);
   printf("%lld\n",res.sum-(long long)res.mins);
  }
 }
 return 0;
}
