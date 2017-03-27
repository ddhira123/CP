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

const int MAXN = 1000005;

int it[MAXN],num[MAXN],low[MAXN];
int vis[MAXN];

vector<int> adj[MAXN], adj2[MAXN];
vector<int> proc,S;

int arr[MAXN];
LL val[MAXN];
int SCC_ID[MAXN];

LL dp[MAXN];
int deg[MAXN];
int n,m,s,t;
int cnt,SCC_cnt;

void Read(){
 scanf("%d %d %d %d",&n,&m,&s,&t);
 for(int i = 1 ; i <= n ; i++){
  scanf("%d",&arr[i]);
  num[i] = low[i] = vis[i] = -1;
 }
 for(int i = 1 ; i <= m ; i++){
  int a,b;
  scanf("%d %d",&a,&b);
  adj[a].pb(b);
 }
 cnt = SCC_cnt = 1;
}

void Tarjan(int st){
 proc.pb(st);
 while(!proc.empty()){
  int now = proc.back();
  
  if(num[now] == -1){
   num[now] = low[now] = cnt++;
   S.pb(now);
   vis[now] = 1;
  }
  
  for(; it[now] < adj[now].size() ;){
   int nxt = adj[now][it[now]];
   if(vis[nxt] == -1){
    proc.pb(nxt);
    break;
   }
   else{
    if(vis[nxt]) low[now] = min(low[now],low[nxt]);
    it[now]++;
   }
  }
  
  if(it[now] == adj[now].size()){
   proc.pop_back();
   if(num[now] == low[now]){
    //printf("SCC %d ->",SCC_cnt);
    while(1){
     int u = S.back() ; S.pop_back();
     low[u] = low[now];
     val[SCC_cnt] += arr[u];
     vis[u] = 0;
     SCC_ID[u] = SCC_cnt;
     //printf(" %d",u);
     if(u == now) break;
    }
    //puts("");
    dp[SCC_cnt] = -INFLL;
    SCC_cnt++;
   }
  }
 }
}

void Init(){
 for(int i = 1 ; i <= n ; i++)
  if(vis[i] == -1)
   Tarjan(i);
 for(int i = 1 ; i <= n ; i++)
  for(int j = 0 ; j < adj[i].size() ; j++){
   int nxt = adj[i][j];
   if(SCC_ID[i] != SCC_ID[nxt]){
    int lol = SCC_ID[i],lol2 = SCC_ID[nxt];
    adj2[lol].pb(lol2);
    deg[lol2]++;
   }
  }  
}

void Solve(){
 dp[SCC_ID[s]] = 0;
 queue<int> q;
 for(int i = 1 ; i < SCC_cnt ; i++)
  if(deg[i] == 0) 
    q.push(i);
 while(!q.empty()){
  int now = q.front(); q.pop();
  dp[now] += val[now];
  for(int i = 0 ; i < adj2[now].size() ; i++){
   int nxt = adj2[now][i];
   dp[nxt] = max(dp[nxt],dp[now]);
   deg[nxt]--;
   if(deg[nxt] == 0)
    q.push(nxt);
  }
 }
 printf("%lld\n",dp[SCC_ID[t]]);   
}

int main(){
 Read();
 Init();
 Solve();
 //puts("ganteng");
 return 0;
}
