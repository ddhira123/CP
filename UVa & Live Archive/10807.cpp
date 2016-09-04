#include <cstdio>
#include <vector>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define INF 1000000000

pair<int,pii> line[30];
int n,m,ans;
int par[2][15];
int used[30];

inline int finds(int haha,int x){
 return (x==par[haha][x] ? x : par[haha][x]=finds(haha,par[haha][x]));
}

inline void uni(int haha,int x,int y){
 par[haha][finds(haha,y)]=finds(haha,x);
}

inline bool issame(int haha,int x,int y){
 return finds(haha,x)==finds(haha,y);
}

inline void reset(int haha){
 for(int i=0;i<n;i++)
  par[haha][i]=i;
}

inline int kruskal(int mask){
 int cnt=n-1,ret=0;
 reset(1);
 //printf("%d\n",mask);
 for(int i=0;i<m && cnt;i++)
  if((mask&(1<<i))==0){
   int a=line[i].se.fi;
   int b=line[i].se.se;
   int c=line[i].fi;
   if(!issame(1,a,b))
    ret+=c,uni(1,a,b),cnt--;
  }
 if(cnt) ret=INF; 
 return ret;
}



void brute(int pos,int need,int sum,int mask){
 if(need==0){
  ans=min(ans,sum+kruskal(mask));
 }
 //else if(m-pos<need) return;
 else{
  for(int i=pos;i<m;i++){
   int a=line[i].se.fi;
   int b=line[i].se.se;
   int c=line[i].fi;
   //int tmp1=finds(0,a);
   //int tmp1=finds(0,b);
   if(!issame(0,a,b)){
    //int tmp1=par[0][a],tmp2=par[0][b];
    uni(0,a,b);
    brute(i+1,need-1,sum+c,mask|(1<<i));
   }
  }
 } 
}

inline int proc(){
 int ret=0;
 int mask=0;
 reset(0);
 for(int i=0;i<n-1;i++){
  mask|=(1<<used[i]);
  int a=line[used[i]].se.fi;
  int b=line[used[i]].se.se;
  int c=line[used[i]].fi;
  if(!issame(0,a,b))
   ret+=c,uni(0,a,b);
  else
   return INF; 
 }
 return ret+kruskal(mask);
}

void brute(int pos,int need){
 if(need==-1){
  int tmp=proc();
  if(tmp<ans){
   ans=tmp;
  }
 } 
 else if(m-pos<need+1) return; 
 else{
  for(int i=pos;i<m;i++)
   used[need]=i,brute(i+1,need-1);
 } 
}

int main(){
 scanf("%d",&n);
 while(n){
  scanf("%d",&m);
  for(int i=0;i<m;i++){
   scanf("%d %d %d",&line[i].se.fi,&line[i].se.se,&line[i].fi);
   line[i].se.fi--;
   line[i].se.se--;
  }
  sort(line,line+m); 
  ans=INF;
  reset(0);
  brute(0,n-1,0,0);
  if(ans==INF)
   puts("No way!");
  else
   printf("%d\n",ans); 
  /*brute(0,n-2);
  if(ans==INF)
   puts("No way!");
  else
   printf("%d\n",ans);*/ 
  scanf("%d",&n); 
 }
 return 0;
}
