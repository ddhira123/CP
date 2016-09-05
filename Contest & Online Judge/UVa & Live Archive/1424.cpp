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

typedef long long LL;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;
typedef pair<string,string> pss;
typedef pair<int,double> pid;
typedef pair<int,LL> pil;
typedef pair<LL,LL> pll;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define TIE cin.tie(0)
#define g getchar_unlocked
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL
#define DEBUG puts("DEBUG")


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

int dp[105][205];
vector<int> adj[105];
int tgt[205];
int n,m,x,tc,a,b;

inline int PlayDP(){
 for(int i=1;i<=n;i++)
  dp[i][0]=(tgt[0]!=i);
 for(int i=0;i<x-1;i++){
  for(int j=1;j<=n;j++)
   dp[j][i+1]=INF;
  for(int j=1;j<=n;j++)
   for(int k=0;k<adj[j].size();k++){
    int nxt=adj[j][k];
    dp[nxt][i+1]=min(dp[nxt][i+1],dp[j][i]+(tgt[i+1]!=nxt));
   } 
 }
 int ans=INF;
 for(int i=n;i>=1;i--)
  ans=min(ans,dp[i][x-1]);
 return ans;  
}

int main(){
 tc=io();
 while(tc--){
  n=io(),m=io();
  for(int i=1;i<=n;i++)
   adj[i].clear(),adj[i].pb(i);
  while(m--){
   a=io(),b=io();
   adj[a].pb(b);
   adj[b].pb(a);
  } 
  x=io();
  for(int i=0;i<x;i++)
   tgt[i]=io();
  printf("%d\n",PlayDP()); 
 }
 //puts("ganteng");
 return 0;
}

