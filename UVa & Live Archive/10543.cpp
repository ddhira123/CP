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

bool dp[55][25];
int n,m,a,b,q;
vector<int> adj[55];

inline void PlayDP(){
 for(int i=0;i<n;i++)
  for(int j=0;j<=20;j++)
   dp[i][j]=0;
 dp[0][1]=1;
 for(int j=1;j<=20;j++)
  for(int i=0;i<n;i++)
   if(dp[i][j]) 
    for(int k=0;k<adj[i].size();k++)
     dp[adj[i][k]][j+1]=1;
 bool found=0;    
 for(int i=m;i<=20;i++)
  if(dp[n-1][i]){
   printf("%d\n",i);
   found=1;
   break;
  } 
 if(!found) 
  puts("LOSER");    
}

int main(){
 scanf("%d %d %d",&n,&q,&m);
 while(n|m|q){
  for(int i=0;i<n;i++) adj[i].clear();
  while(q--){
   scanf("%d %d",&a,&b);
   adj[a].pb(b);
  }
  PlayDP();
  scanf("%d %d %d",&n,&q,&m);
 }
 //puts("ganteng");
 return 0;
}

