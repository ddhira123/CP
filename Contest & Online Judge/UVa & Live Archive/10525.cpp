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

int dist[55][55],tim[55][55];
int tc,n,m,q;
int x,y,dum,tmp;

inline void Warshall(){
 for(int i=1;i<=n;i++)
  for(int j=1;j<=n;j++)
   for(int k=1;k<=n;k++)
    if(tim[j][k] > tim[j][i]+tim[i][k] || (tim[j][k] == tim[j][i]+tim[i][k] && dist[j][k] > dist[j][i]+dist[i][k])){
     tim[j][k]=tim[j][i]+tim[i][k];
     dist[j][k]=dist[j][i]+dist[i][k];
    }
}

inline void Reset(){
 for(int i=1;i<=n;i++){
  for(int j=1;j<=n;j++)
   dist[i][j]=tim[i][j]=INF;
  dist[i][i]=tim[i][i]=0; 
 }
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&n,&m);
  Reset();
  while(m--){
   scanf("%d %d %d %d",&x,&y,&dum,&tmp);
   if(tim[x][y]>dum || (tim[x][y]==dum && dist[x][y]>tmp))
    tim[x][y]=dum,dist[x][y]=tmp;
   tim[y][x]=tim[x][y];
   dist[y][x]=dist[x][y]; 
  }
  Warshall();
  scanf("%d",&q);
  while(q--){
   scanf("%d %d",&x,&y);
   if(tim[x][y]==INF)
    puts("No Path.");
   else
    printf("Distance and time to reach destination is %d & %d.\n",dist[x][y],tim[x][y]); 
  }
  if(tc)
   puts("");
 }
 //puts("ganteng");
 return 0;
}

