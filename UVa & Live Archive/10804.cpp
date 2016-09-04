#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <bitset>
#include <cassert>
#define makmu using
#define ndasmu namespace
#define gundulmu std

makmu ndasmu gundulmu;

typedef pair<int,int> pii;
typedef long long LL;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define g getchar_unlocked
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL

int dx8[8]={-1,-1,0,1,1,1,0,-1},dx4[4]={-1,0,1,0};
int dy8[8]={0,-1,-1,-1,0,1,1,1},dy4[4]={0,-1,0,1};

inline void open(string name){
 freopen((name+".in").c_str(),"r",stdin);
 freopen((name+".out").c_str(),"w",stdout);
}

inline void close(){
 fclose(stdin);
 fclose(stdout);
}

inline int io(){
 register char c;
 while(1){
  c=g();
  if(c!='\n' && c!=' ') break;
 }
 int res=0,sign=1;
 if(c=='-') sign=-1;
 else       res=c-'0';
 while(1){
  c=g();
  if(c==' ' || c=='\n' || c==EOF) break;
  res=(res<<3)+(res<<1)+c-'0';
 }
 return res*sign;
}

///////////////////////////////////////////////////
//////            End of Template            /////
/////////////////////////////////////////////////

pair<double,double> coord[105];
int n,m,k,tc;

vector<int> adj[55];
bool vis[55];
int match[105];

inline void MakeAdj(double x){
 for(int i=1;i<=n;i++) adj[i].clear();
 for(int i=1;i<=m;i++){
  match[n+i]=-1;
  for(int j=1;j<=n;j++)
   if(hypot(coord[j].fi-coord[n+i].fi,coord[j].se-coord[n+i].se)<x+EPS)
    adj[j].pb(n+i);
 }
}

int Augment(int x){
 if(vis[x]) return 0;
 vis[x]=1;
 for(int i=0;i<adj[x].size();i++){
  int y=adj[x][i];
  if(match[y]==-1 || Augment(match[y])){
   match[y]=x;
   return 1;
  }
 }
 return 0;
}

inline int MCBM(double x){
 MakeAdj(x);
 int ret=0;
 for(int i=1;i<=n;i++){
  for(int j=1;j<=n;j++) vis[j]=0;
  ret+=Augment(i);
 }
 return ret;
}

int main(){
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
  scanf("%d %d %d",&n,&m,&k);
  for(int i=1;i<=n+m;i++)
   scanf("%lf %lf",&coord[i].fi,&coord[i].se);
  printf("Case #%d:\n",t);
  if(n-k>m) puts("Too bad.");
  else{
   double lo=0.0,hi=0.0;
   for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
     hi=max(hi,hypot(coord[i].fi-coord[n+j].fi,coord[i].se-coord[n+j].se));
   while(fabs(lo-hi)>1e-5){
    double mid=(lo+hi)/2.0;
    if(n-MCBM(mid)<=k) hi=mid;
    else               lo=mid;
   }
   printf("%.3lf\n",lo);  
  } 
  puts("");
 }
 //puts("ganteng");
 return 0;
}

