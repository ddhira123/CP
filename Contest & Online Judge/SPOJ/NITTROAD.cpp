#include <cstdio>
#include <algorithm>
using namespace std;
#define fi first
#define se second
int tc,n,q,par[20005],siz[20005],op[20005],ans,query[20005],cnt;
pair<int,int> edge[20005];
bool used[20005];
char c[5];
int finds(int i){
 if(i==par[i])
  return i;
 return par[i]=finds(par[i]);
}

bool issame(int i,int j){
 return finds(i)==finds(j);
}

void uni(int i,int j){
 ans-=(siz[finds(i)]*siz[finds(j)]);
 siz[finds(i)]+=siz[finds(j)];
 siz[finds(j)]=0;
 par[finds(j)]=finds(i);
}

void gen(){
 for(int i=1;i<=n;i++){
  par[i]=i;
  siz[i]=1;
  used[i]=0;
 }
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  gen();
  for(int i=1;i<n;i++)
   scanf("%d %d",&edge[i].fi,&edge[i].se);
  scanf("%d",&q);
  for(int i=0;i<q;i++){
   scanf("%s",c);
   if(c[0]=='Q')
    op[i]=0;
   else{
    int dum;
    scanf("%d",&dum);
    op[i]=dum;
    used[dum]=1;
   }
  }
  ans=n*(n-1)/2;
  for(int i=1;i<n;i++)
   if(!used[i]&&!issame(edge[i].fi,edge[i].se))
    uni(edge[i].fi,edge[i].se);
  cnt=0;
  for(int i=q-1;i>=0;i--)
   if(op[i]==0)
     query[cnt++]=ans;
   else if(!issame(edge[op[i]].fi,edge[op[i]].se))
    uni(edge[op[i]].fi,edge[op[i]].se);
  for(int i=cnt-1;i>=0;i--)
   printf("%d\n",query[i]);
  printf("\n");
 }
 return 0;
}
