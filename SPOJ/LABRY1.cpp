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
typedef unsigned long long ULL;
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

int r,c,tc;
char arr[1005][1005];
int dist[1005][1005];

inline int Proc(pii id){
 //printf("MULAI %d %d\n",id.fi,id.se);
 vector<pii> v;
 dist[id.fi][id.se]=0;
 queue<pii> q;
 q.push(id);
 while(!q.empty()){
  pii pos=q.front();
  //printf("%d %d\n",pos.fi,pos.se);
  q.pop();
  v.pb(pos);
  for(int i=0;i<4;i++){
   int nr=pos.fi + dx4[i];
   int nc=pos.se + dy4[i];
   if(nr>=0 && nr<r && nc>=0 && nc<c && arr[nr][nc]=='.' && dist[nr][nc]==-1)
    dist[nr][nc]=dist[pos.fi][pos.se]+1,q.push(mp(nr,nc));
  }
 }
 int maxx=-1;
 //DEBUG;
 for(int i=0;i<v.size();i++){
  pii lol=v[i];
  //printf("%d %d\n",lol.fi,lol.se);
  if(dist[lol.fi][lol.se] > maxx) maxx=dist[lol.fi][lol.se],id=lol;
  dist[lol.fi][lol.se]=-1;
 }
 dist[id.fi][id.se]=0;
 q.push(id);
 while(!q.empty()){
  pii pos=q.front();
  q.pop();
  for(int i=0;i<4;i++){
   int nr=pos.fi + dx4[i];
   int nc=pos.se + dy4[i];
   if(nr>=0 && nr<r && nc>=0 && nc<c && arr[nr][nc]=='.' && dist[nr][nc]==-1)
    dist[nr][nc]=dist[pos.fi][pos.se]+1,q.push(mp(nr,nc));
  }
 }
 for(int i=0;i<v.size();i++)
  /*printf("%d %d %d\n",v[i].fi,v[i].se,dist[v[i].fi][v[i].se]),*/maxx=max(maxx,dist[v[i].fi][v[i].se]); 
 return maxx; 
}


int main(){
 scanf("%d",&tc);
 while(tc--){
 //DEBUG;
  scanf("%d %d",&c,&r);
  for(int i=0;i<r;i++){
   scanf("%s",arr[i]);
   for(int j=0;j<c;j++)
    dist[i][j]=-1;
  }
  //DEBUG; 
  int ans=0;
  bool sudah=0; 
  for(int i=0;i<r && !sudah;i++)
   for(int j=0;j<c && !sudah;j++)
    if(arr[i][j]=='.' && dist[i][j]==-1)
     ans=max(ans,Proc(mp(i,j))),sudah=1;
  printf("Maximum rope length is %d.\n",ans);    
 }  
 //puts("ganteng");
 return 0;
}

