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

int match[205];
vector<int> adj[105];
bool vis[105];

int arr[105];
int tc,n,m,a;

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

inline int MCBM(){
 int ret=0;
 for(int i=1;i<=n;i++){
  for(int j=1;j<=n;j++) vis[j]=0;
  ret+=Augment(i);
 }
 return ret;
}

int main(){
 tc=io();
 for(int t=1;t<=tc;t++){
  n=io();
  for(int i=1;i<=n;i++){
   adj[i].clear();
   arr[i]=io();
  }
  m=io();
  for(int i=1;i<=m;i++){
   match[n+i]=-1;
   a=io();
   for(int j=1;j<=n;j++)
    if((arr[j]!=0 && a%arr[j]==0) || (arr[j]==a)) 
     adj[j].pb(n+i);
  }
  printf("Case %d: %d\n",t,MCBM());
 }
 //puts("ganteng");
 return 0;
}

