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

pii red[105],blue[105];
pii tmp;
int szr,szb;
int n,m,tc;
char c[10];

vector<int> adj[105];
bool vis[105];
int match[205];

inline int sqr(int x){
 return x*x;
}

inline void makeadj(int k){
 for(int i=1;i<=szr;i++)
  adj[i].clear();
 for(int i=1;i<=szb;i++){
  match[i+szr]=-1;
  for(int j=1;j<=szr;j++)
   if(sqr(red[j].fi-blue[i].fi)+sqr(red[j].se-blue[i].se)<=sqr(k))
    adj[j].pb(i+szr);
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

inline int MCBM(int k){
 makeadj(k);
 int ret=0;
 for(int i=1;i<=szr;i++){
  for(int j=1;j<=szr;j++) vis[j]=0;
  ret+=Augment(i);
 }
 return ret;
}

int main(){
 tc=io();
 while(tc--){
  szr=szb=0;
  n=io(),m=io();
  while(n--){
   tmp.fi=io(),tmp.se=io();
   scanf("%s",c);
   if(c[0]=='b') blue[++szb]=tmp;
   else          red[++szr]=tmp;
  }
  if(min(szr,szb)<m) puts("Impossible");
  else{
   int lo=0,hi=3000;
   while(lo<hi){
    int mid=(lo+hi)>>1;
    if(MCBM(mid)>=m) hi=mid;
    else             lo=mid+1;
   }
   printf("%d\n",lo);
  }
 }
 //puts("ganteng");
 return 0;
}

