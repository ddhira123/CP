#include <cstdio>
using namespace std;

bool shieve[1000005];
int arr[10005],q,op,a,b,v,tc,n;
struct tree{
 int lazy;
 int sum;
}seg[50005];

void build(int id,int l,int r){
 if(l==r)
  seg[id].lazy=0,seg[id].sum=(!shieve[arr[l]]);
 else{
  int m=(l+r)>>1,chld=id<<1;
  build(chld+1,l,m);
  build(chld+2,m+1,r);
  seg[id].lazy=0;
  seg[id].sum=seg[chld+1].sum+seg[chld+2].sum;
 }
}

void update(int id,int l,int r,int x,int y,int val){
 if(x<=l && r<=y){
  seg[id].lazy=val;
  seg[id].sum=(r-l+1)*(!shieve[val]);
 }
 else{
  int m=(l+r)>>1,chld=id<<1;
  if(seg[id].lazy!=0){
   seg[chld+1].lazy=seg[id].lazy;
   seg[chld+2].lazy=seg[id].lazy;
   seg[chld+1].sum=(m-l+1)*(!shieve[seg[id].lazy]);
   seg[chld+2].sum=(r-m)*(!shieve[seg[id].lazy]);
   seg[id].lazy=0;
  }
  if(x<=m) update(chld+1,l,m,x,y,val);
  if(y>m)  update(chld+2,m+1,r,x,y,val);
  seg[id].sum=seg[chld+1].sum+seg[chld+2].sum;
 }
}

int query(int id,int l,int r,int x,int y){
 if(x<=l && r<=y)
  return seg[id].sum;
 else{
  int m=(l+r)>>1,chld=id<<1;
  if(seg[id].lazy!=0){
   seg[chld+1].lazy=seg[id].lazy;
   seg[chld+2].lazy=seg[id].lazy;
   seg[chld+1].sum=(m-l+1)*(!shieve[seg[id].lazy]);
   seg[chld+2].sum=(r-m)*(!shieve[seg[id].lazy]);
   seg[id].lazy=0;
  }
  seg[id].sum=seg[chld+1].sum+seg[chld+2].sum;
  int ret=0;
  if(x<=m) ret+=query(chld+1,l,m,x,y);
  if(y>m)  ret+=query(chld+2,m+1,r,x,y);
  return ret;
 }
}

int main(){
 shieve[1]=shieve[0]=1;
 for(int i=2;i<=1000000;i++)
  if(!shieve[i])
   for(int j=i;j<=1000000/i;j++)
    shieve[i*j]=1;
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
  scanf("%d %d",&n,&q);
  for(int i=1;i<=n;i++)
   scanf("%d",&arr[i]);
  build(0,1,n);
  printf("Case %d:\n",t);
  while(q--){
   scanf("%d %d %d",&op,&a,&b);
   if(op)
    printf("%d\n",query(0,1,n,a,b));
   else{
    scanf("%d",&v);
    update(0,1,n,a,b,v);
   }
  }
 }
 return 0;
}