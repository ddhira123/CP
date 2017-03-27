#include <cstdio>
#include <algorithm>
using namespace std;
#define fi first
#define se second
#define mp make_pair
typedef pair<int,int> pii;

pii tree[1000005];
int arr[1000005],n,m,a,b;
char z;

bool cmp(int i,int j){
 return arr[i]>arr[j];
}

pii srot(pii i,pii j){
 int tmp[4]={i.fi,i.se,j.fi,j.se};
 sort(tmp,tmp+4,cmp);
 return mp(tmp[0],tmp[1]);
}

void build(int id,int l,int r){
 if(l==r)
  tree[id]=mp(l,n);
 else{
  int m=(l+r)/2;
  build(2*id+1,l,m);
  build(2*id+2,m+1,r);
  tree[id]=srot(tree[2*id+1],tree[2*id+2]);
 }
}

void update(int id,int l,int r,int x){
 if(l<r){
  int m=(l+r)/2;
  if(x<=m) update(2*id+1,l,m,x);
  else     update(2*id+2,m+1,r,x);
  tree[id]=srot(tree[2*id+1],tree[2*id+2]);
 }
}

pii query(int id,int l,int r,int x,int y){
 if(x<=l&&r<=y)
  return tree[id];
 else{
  int m=(l+r)/2;
  pii tmp=mp(n,n),tmp2=mp(n,n);
  if(x<=m) tmp=query(2*id+1,l,m,x,y);
  if(m<y)  tmp2=query(2*id+2,m+1,r,x,y);
  return srot(tmp,tmp2);
 }
}


int main(){
 scanf("%d",&n);
 for(a=0;a<n;a++)
  scanf("%d",&arr[a]);
 arr[n]=-1;
 build(0,0,n-1);
 scanf("%d",&m);
 while(m--){
  getchar();
  scanf("%c %d %d",&z,&a,&b);
  a--;
  if(z=='U'){
   arr[a]=b;
   update(0,0,n-1,a);
  }
  else{
   b--;
   pii res=query(0,0,n-1,a,b);
   printf("%d\n",arr[res.fi]+arr[res.se]);
  }
 }
 return 0;
}
