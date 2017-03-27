#include <cstdio>
using namespace std;

int par[100005],n,q,a,b;

int finds(int x){
 if(x==par[x])
  return x;
 return par[x]=finds(par[x]);
}

void uni(int i,int j){
 par[finds(i)]=finds(j);
}

bool issame(int i,int j){
 return finds(i)==finds(j);
}

int main(){
 scanf("%d%d",&n,&q);
 for(a=0;a<=n;a++)
  par[a]=a;
 while(q--){
  scanf("%d%d",&a,&b);
  if(!issame(a,b))
   uni(a,b);
 }
 scanf("%d",&q);
 while(q--){
  scanf("%d%d",&a,&b);
  if(issame(a,b))
   printf("YES\n");
  else
   printf("NO\n");
 }
 return 0;
}