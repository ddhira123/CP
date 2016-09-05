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
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL
#define DEBUG puts("DEBUG")

#ifdef _WIN32
#define getchar_unlocked getchar
#endif

#define g getchar_unlocked

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

int tc,dist[105][105];
int arr[105][105];
int n1,n2,n3;
int n;

inline void BFS(){
 dist[n1][n2]=0;
 queue<pii> q;
 q.push(mp(n1,n2));
 while(!q.empty()){
  pii pos=q.front();q.pop();
  if(pos.fi==n3 || pos.se==n3){
   printf("Minimum Number of Moves = %d\n",dist[pos.fi][pos.se]);
   return;
  }
  if(arr[pos.fi][pos.se]!=0 && dist[arr[pos.fi][pos.se]][pos.se]==INF)
   q.push(mp(arr[pos.fi][pos.se],pos.se)),dist[arr[pos.fi][pos.se]][pos.se]=dist[pos.fi][pos.se]+1;
  if(arr[pos.se][pos.fi]!=0 && dist[pos.fi][arr[pos.se][pos.fi]]==INF)
   q.push(mp(pos.fi,arr[pos.se][pos.fi])),dist[pos.fi][arr[pos.se][pos.fi]]=dist[pos.fi][pos.se]+1;    
 }
 puts("Destination is Not Reachable !");
}

int main(){
 n=io();
 while(n){
  for(int i=1;i<=n;i++)
   for(int j=1;j<=n;j++)
    dist[i][j]=INF,arr[i][j]=io();
  n1=io(),n2=io(),n3=io();
  printf("Game #%d\n",++tc);
  BFS();
  puts("");
  n=io();
 }
 //puts("ganteng");
 return 0;
}

