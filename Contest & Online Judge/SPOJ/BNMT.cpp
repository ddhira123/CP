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
char s[50][50];
int flow[90][90],cost[90][90];
vector<int> adj[90];
int dist[90],par[90];
bool in[90];
int it[90];

void Make_Adj(){
 for(int i = 0 ; i <= r+c+1 ; i++)
  adj[i].clear();
 for(int i = 1 ; i <= r ; i++){
  adj[0].pb(i), adj[i].pb(0);
  cost[0][i] = cost[i][0] = 0;
 }
 for(int i = 1 ; i <= c ; i++){
  adj[r+i].pb(r+c+1), adj[r+c+1].pb(r+i);
  cost[r+i][r+c+1] = cost[r+c+1][r+i] = 0;
 }
 for(int i = 1 ; i <= r ; i++)
  for(int j = 1 ; j <= c ; j++){
   adj[i].pb(r+j);
   adj[r+j].pb(i);
   //printf("%d %d -> %c\n",i,j,s[i-1][j-1]);
   if(s[i-1][j-1] == '1')
    cost[i][r+j] = 0;
   else
    cost[i][r+j] = 1;
   cost[r+j][i] = -cost[i][r+j];
   //printf("%d %d -> %d\n",i,j,cost[i][r+j]);
  }
}

void Reset(int x){
 for(int i = 1 ; i <= r ; i++){
  flow[0][i] = x;
  flow[i][0] = 0;
 }
 for(int i = 1 ; i <= c ; i++){
  flow[r+i][r+c+1] = r*x/c;
  flow[r+c+1][r+i] = 0;
 }
 for(int i = 1 ; i <= r ; i++)
  for(int j = 1 ; j <= c ; j++){
   flow[i][r+j] = 1;
   flow[r+j][i] = 0;
  }
}

void SPFA(){
 for(int i = 0 ; i <= r+c+1 ; i++){
  dist[i] = INF;
  in[i] = 0;
  par[i] = -1;
 }
 queue<int> q;
 dist[0] = 0;
 in[0] = 1;
 q.push(0);
 while(!q.empty()){
  int pos = q.front();
  //printf("%d\n",pos);
  q.pop();
  in[pos] = 0;
  //if(par[pos] != -1 && in[par[pos]]) continue;
  for(int i = 0 ; i < adj[pos].size() ; i++){
   int nxt = adj[pos][i];
   if(flow[pos][nxt] > 0 && dist[pos] + cost[pos][nxt] < dist[nxt]){
     dist[nxt] = dist[pos] + cost[pos][nxt];
     par[nxt] = pos;
     if(!in[nxt])
      in[nxt] = 1,q.push(nxt);
   }
  }
 }
}

int f;

void Augment(int pos,int mins){
 if(pos == 0) f = mins;
 else if(mins == 0) return;
 else{
  Augment(par[pos],min(mins,flow[par[pos]][pos]));
  flow[par[pos]][pos] -= f;
  flow[pos][par[pos]] += f;
 }
}

int MCMF(int x){
 Reset(x);
 int ret = 0;
 while(1){
  SPFA();
  if(dist[r+c+1] == INF) break;
  int tot = 0;
  for(int i = r+1 ; i <= r+c ; i++)
   if(dist[i] + cost[i][r+c+1] == dist[r+c+1] && flow[i][r+c+1] > 0){
    f = 0;
    Augment(i,flow[i][r+c+1]);
    tot += f;
    flow[i][r+c+1] -= f;
    flow[r+c+1][i] += f;
   }
  ret += tot*dist[r+c+1];
 }
 for(int i = 1 ; i <= r ; i++)
  for(int j = 1 ; j <= c ; j++)
   if(s[i-1][j-1] == '1' && flow[i][r+j] > 0)
    ret++;
 //printf("RES %d -> %d\n",x,ret);
 return ret;
}

int main(){
 scanf("%d",&tc);
 for(int t = 1 ; t <= tc ; t++){
  scanf("%d %d",&r,&c);
  for(int i = 0 ; i < r ; i++)
   scanf("%s",s[i]);
  Make_Adj();
  int ans = INF;
  for(int i = 0 ; i <= c ; i++)
   if((i*r)%c == 0){
    int haha = MCMF(i);
    if(ans > haha) ans = haha;
    else break;
   }
  printf("Case %d: %d\n",t,ans);
 }
 return 0;
}
