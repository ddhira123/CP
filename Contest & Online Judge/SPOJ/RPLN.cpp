#include <cstdio>
#include <algorithm>
using namespace std;
#define INF 1000000001

int tree[500005],n,arr[100005],q,a,b,tc,i;

void build(int id,int l,int r){
 if(l==r)
  tree[id]=arr[l];
 else{
  int m=(l+r)>>1;
  build((id<<1)+1,l,m);
  build((id<<1)+2,m+1,r);
  tree[id]=min(tree[(id<<1)+1],tree[(id<<1)+2]);
 }
}

int query(int id,int l,int r,int x,int y){
 if(x<=l&&r<=y)
  return tree[id];
 else{
  int m=(l+r)>>1,ans=INF;
  if(x<=m) ans=min(ans,query((id<<1)+1,l,m,x,y));
  if (m<y) ans=min(ans,query((id<<1)+2,m+1,r,x,y));
  return ans;
 }
}

int main(){
 scanf("%d",&tc);
 for(i=1;i<=tc;i++){
  scanf("%d%d",&n,&q);
  for(a=1;a<=n;a++)
   scanf("%d",&arr[a]);
  build(0,1,n);
  printf("Scenario #%d:\n\n",i);
  while(q--){
   scanf("%d%d",&a,&b);
   printf("%d\n",query(0,1,n,a,b));
  }
 }
 return 0;
}
