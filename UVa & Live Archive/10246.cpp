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
#define INF 1<<29
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

int dist[85][85],f[85][85];
int n,m,q;
int a,b,x;
int tc;

inline void Reset(){
 for(int i=1;i<=n;i++)
  for(int j=1;j<=n;j++)
   dist[i][j]=f[i][j]=INF;
}

inline void War(){
 for(int i=1;i<=n;i++)
  for(int j=1;j<=n;j++)
   for(int k=1;k<=n;k++)
    if(dist[j][k]+f[j][k]>dist[j][i]+dist[i][k]+max(f[j][i],f[i][k])){
     dist[j][k]=dist[j][i]+dist[i][k];
     f[j][k]=max(f[j][i],f[i][k]);
    }
}

int main(){
 n=io(),m=io(),q=io();
 while(n|m|q){
  Reset();
  for(int i=1;i<=n;i++)
   dist[i][i]=0,f[i][i]=io();
  while(m--){
   a=io(),b=io(),x=io();
   dist[a][b]=min(dist[a][b],x);
   dist[b][a]=dist[a][b];
   f[a][b]=max(f[a][a],f[b][b]);
   f[b][a]=f[a][b];
  }
  War();
  War();
  if(tc) puts("");
  printf("Case #%d\n",++tc);
  while(q--){
   a=io(),b=io();
   x=dist[a][b]+f[a][b];
   if(x>=INF) x=-1;
   printf("%d\n",x);
  }
  n=io(),m=io(),q=io();
 }
 //puts("ganteng");
 return 0;
}

