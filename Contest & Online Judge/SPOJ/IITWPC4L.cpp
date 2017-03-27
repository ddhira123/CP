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

const int MAXV = 3 + 50 + 1500 + 5;

struct edge{
 int from,to;
 int flow,cost;
 
 edge(){}
 
 edge(int a,int b,int c,int d){
  from = a; to = b;
  flow = c; cost = d;
 }
};

int dist[MAXV];
bool in[MAXV];

vector<int> adj[MAXV];
vector<edge> elist;
int par[MAXV];

int ctr;
int n,q,tc;
int key[55],v[55];

void reset(){
 ctr = 0;
 elist.clear();
 for(int i = 0 ; i <= 2 + n + 1501 ; i++)
  adj[i].clear();
}

void add_edge(int a,int b,int c,int d){
 adj[a].pb(ctr++);
 elist.pb(edge(a,b,c,d));
 
 adj[b].pb(ctr++);
 elist.pb(edge(b,a,0,-d));
}


void make(){
 add_edge(0,1,q,0);
 for(int i = 1 ; i <= n ; i++)
  add_edge(1,i+2,1,0);
 for(int i = -250 ; i <= 1250 ; i++)
  add_edge(253 + n + i,2,1,0);
 for(int i = 1 ; i <= n ; i++)
  for(int j = -250 ; j <= 1250 ; j++){
   int id1 = i+2,id2 = 253 + n + j;
   int dis = abs(key[i]-j);
   dis = (dis + v[i] - 1) / v[i];
   add_edge(id1,id2,1,dis);
  }  
}


void SPFA(){
 queue<int> q;
 for(int i = 0 ; i <= 2 + n + 1501 ; i++)
  dist[i] = INF;
 dist[0] = 0;
 in[0] = 1;
 q.push(0);
 while(!q.empty()){
  int pos = q.front();
  q.pop();
  in[pos] = 0;
  for(int i = 0 ; i < adj[pos].size() ; i++){
   int idx = adj[pos][i];
   int nxt = elist[idx].to;
   int ff =  elist[idx].flow;
   int cc =  elist[idx].cost;
   if(ff && dist[pos] + cc < dist[nxt]){
    dist[nxt] = dist[pos] + cc;
    par[nxt] = idx;
    if(!in[nxt])
     in[nxt] = 1, q.push(nxt);
   }
  }
 }  
}

int MCMF(){
 int ans = 0;
 while(1){
  SPFA();
  if(dist[2] == INF) break;
  int pos = 2;
  int mins = INF;
  while(pos != 0){
   int idx = par[pos];
   int ff = elist[idx].flow;
   int fro = elist[idx].from;
   mins = min(mins,ff);
   pos = fro;
  }
  ans += mins * dist[2];
  
  pos = 2;
  while(pos != 0){
   int idx = par[pos];
   int fro = elist[idx].from;
   elist[idx].flow -= mins;
   elist[idx^1].flow += mins;
   pos = fro;
  }
 }
 return ans;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&n,&q);
  for(int i = 1 ; i <= n ; i++)
   scanf("%d",&key[i]);
  for(int i = 1 ; i <= n ; i++)
   scanf("%d",&v[i]);
  reset();
  make();
  printf("%d\n",MCMF());  
 }
 //puts("ganteng");
 return 0;
}
