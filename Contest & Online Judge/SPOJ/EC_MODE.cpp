#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
int n,r,w,dc,tc,par[1005],siz,siz2;
pii co[1005];
pair<int,pii>  up[500005],lo[500005];
double A,B,u,v;

inline int sqr(int x){
 return x*x;
}

inline int dist(int i,int j){
 return sqr(co[i].fi-co[j].fi)+sqr(co[i].se-co[j].se);
}


int finds(int x){
 return (x==par[x] ? x : par[x]=finds(par[x]));
}

int main(){
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
  scanf("%d %d %d %lf %lf",&n,&r,&w,&u,&v);
  siz=siz2=0;
  A=B=0.0;
  dc=n;
  for(int i=0;i<n;i++){
   scanf("%d %d",&co[i].fi,&co[i].se);
   par[i]=i;
   for(int j=0;j<i;j++){
    int yoo=dist(i,j);
    if(yoo<=sqr(r))
     lo[siz++]=(mp(yoo,mp(i,j)));
    else
     up[siz2++]=(mp(yoo,mp(i,j)));
   }
  }
  sort(lo,lo+siz);
  sort(up,up+siz2);
  for(int i=0;i<siz&&dc>w;i++){
   int yee=lo[i].se.fi,yoo=lo[i].se.se;
   if(finds(yee)!=finds(yoo)){
    A+=u*sqrt((double)lo[i].fi);
    dc--;
    par[finds(yee)]=finds(yoo);
   }
  }
  for(int i=0;i<siz2&&dc>w;i++){
   int yee=up[i].se.fi,yoo=up[i].se.se;
   if(finds(yee)!=finds(yoo)){
    B+=v*sqrt((double)up[i].fi);
    dc--;
    par[finds(yee)]=finds(yoo);
   }
  }
  printf("Caso #%d: %.3lf %.3lf\n",t,A,B);
 }
 return 0;
}
