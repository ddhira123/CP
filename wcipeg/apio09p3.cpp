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
#define INF 2000000001
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

const int MAXN = 500005;

vector<int> adj[MAXN];
vector<int> adjS[MAXN];
int num[MAXN], lo[MAXN], vis[MAXN];
int it[MAXN],id[MAXN];
int arr[MAXN], val[MAXN], dp[MAXN];
bool pub[MAXN];
bool pubS[MAXN];
int deg[MAXN];
int n,m,s,p;
int counter,SCC;

void Read(){
 scanf("%d %d",&n,&m);
 
 while(m--){
  int a,b;
  scanf("%d %d",&a,&b);
  adj[a].pb(b);
 }
 
 for(int i = 1 ; i <= n ; i++){
  scanf("%d",&arr[i]); 
  vis[i] = -1;
 } 
 
 scanf("%d %d",&s,&p);
 
 while(p--){
  int a;
  scanf("%d",&a);
  pub[a] = 1;
 } 
}

void Tarjan(int st){
 vector<int> stek,proc;
 proc.pb(st);
 
 while(!proc.empty()){
  int now = proc.back();
  if(vis[now] == -1){
   num[now] = lo[now] = counter++;
   vis[now] = 1;
   stek.pb(now);
  }
  
  for(; it[now] < adj[now].size() ;){
   int nxt = adj[now][it[now]];
   if(vis[nxt] == -1){
    proc.pb(nxt);
    break;
   }
   else{
    if(vis[nxt]) lo[now] = min(lo[now],lo[nxt]);
    it[now]++;
   }
  }
  
  if(it[now] < adj[now].size()) continue;
  
  proc.pop_back();
  
  if(num[now] == lo[now]){
   while(1){
    int u = stek.back();
    stek.pop_back();
    val[SCC] += arr[u];
    pubS[SCC] |= pub[u];
    id[u] = SCC;
    vis[u] = 0;
    if(u == now) break;
   }
   
   SCC++;
  }
 }
}

void Make_Graph(){

 for(int i = 1 ; i <= n ; i++)
  if(vis[i] == -1)
   Tarjan(i);
 
 for(int i = 1 ; i <= n ; i++)
  for(int j = 0 ; j < adj[i].size() ; j++){
   int nxt = adj[i][j];
   if(id[i] != id[nxt]){
    adjS[ id[i] ].pb(id[nxt]);
    deg[ id[nxt] ]++;
   }
  }
}

void Solve(){
 int ans = -INF;
 queue<int> q;
 
 for(int i = 0 ; i < SCC ; i++){
  dp[i] = - INF;
  if(deg[i] == 0)
   q.push(i);
 }
 dp[ id[s] ] = 0;
 
 while(!q.empty()){
  int now = q.front();
  q.pop();
  dp[now] += val[now];
  if(pubS[now]) ans = max(ans,dp[now]);
  
  for(int i = 0 ; i < adjS[now].size() ; i++){
   int nxt = adjS[now][i];
   dp[nxt] = max(dp[nxt],dp[now]);
   deg[nxt]--;
   if(deg[nxt] == 0)
    q.push(nxt);
  }
 }
 
 printf("%d\n",ans);
}

int main(){
 Read();
 Make_Graph();
 Solve();
 //puts("ganteng");
 return 0;
}

