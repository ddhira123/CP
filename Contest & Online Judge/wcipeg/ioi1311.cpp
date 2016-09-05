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

vector<pil> adj[100005];
pil Path[100005][2];
int n,k;
LL l;
vector<int> v;
bool vis[100005];
LL Center[3];
LL ans;
LL dist[100005];
int ctr;

void dfs1(int las,int now){
 v.pb(now);
 vis[now]=1;
 for(int i=0;i<adj[now].size();i++){
  int nxt=adj[now][i].fi;
  if(nxt!=las){
   dist[nxt]=dist[now]+adj[now][i].se;
   dfs1(now,nxt);
   LL cost=adj[now][i].se+Path[nxt][0].se;
   if(cost > Path[now][0].se)
    Path[now][1]=Path[now][0],Path[now][0]=mp(nxt,cost);
   else if(cost > Path[now][1].se)
    Path[now][1]=mp(nxt,cost); 
  }
 }
}

void dfs2(int las,int now){
 for(int i=0;i<adj[now].size();i++){
  int nxt=adj[now][i].fi;
  LL cost=adj[now][i].se;
  for(int j=0;j<2;j++)
   if(Path[now][j].fi!=nxt){
   if(cost+Path[now][j].se > Path[nxt][0].se)
    Path[nxt][1]=Path[nxt][0],Path[nxt][0]=mp(now,cost+Path[now][j].se);
   else if(cost+Path[now][j].se > Path[nxt][1].se)
    Path[nxt][1]=mp(now,cost+Path[now][j].se); 
   }
  if(nxt!=las)
   dfs2(now,nxt); 
 }
}

inline void Process(int x){
 v.clear();
 dfs1(-1,x);
 LL maks=-1;
 int idx;
 for(int i=0;i<v.size();i++){
  if(maks < dist[v[i]])
   maks=dist[v[i]],idx=v[i];
  Path[v[i]][0]=Path[v[i]][1]=mp(-1,0); 
 }  
 v.clear();
 dist[idx]=0;
 dfs1(-1,idx);
 dfs2(-1,idx);
 LL mini=INFLL;
 
 for(int i=0;i<v.size();i++)
  mini=min(mini,Path[v[i]][0].se),ans=max(ans,dist[v[i]]);   
 for(int i=0;i<v.size();i++){
  //cout<<v[i]<<" "<<Path[v[i]][0].fi<<" "<<Path[v[i]][0].se<<" "<<dist[v[i]]<<"\n";
 } 
  if(Center[2] < mini)
   Center[2]=mini;
  if(Center[2] > Center[1]) swap(Center[1],Center[2]);
  if(Center[1] > Center[0]) swap(Center[0],Center[1]); 
 ctr++; 
}

int main(){
 SYNC;
 cin>>n>>k>>l;
 for(int i=0;i<n;i++)
  Path[i][0]=Path[i][1]=mp(-1,0);
 ans=-1;
 while(k--){
  int a,b,d;
  cin>>a>>b>>d;
  adj[a].pb(mp(b,d));
  adj[b].pb(mp(a,d));
 }
 for(int i=0;i<n;i++)
  if(!vis[i]) Process(i);
 //cout<<Center[0]<<" "<<Center[1]<<" "<<Center[2]<<"\n";  
 if(ctr>1)
 ans=max(ans,l+Center[0]+Center[1]);
 if(ctr>2)
 ans=max(ans,2LL*l+Center[1]+Center[2]);
 cout<<ans<<"\n"; 
 //puts("ganteng");
 return 0;
}

