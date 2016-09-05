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

vector<int> In,masuk;
vector<pii> lol;
vector<pii> adj[200005];
int n,k;
int a,b,d;
int sz[200005];
bool vis[200005],flag[200005]; //flag mark yang pernah jadi center, vis as its meaning
queue<int> q;
int match[1000005];
int ans=INF;
int maks[200005];

void dfs1(int pos){ //finding size of biggest child
 vis[pos]=1;
 sz[pos]=0;
 maks[pos]=0;
 In.pb(pos);
 for(int i=0;i<adj[pos].size();i++){
  int nxt=adj[pos][i].fi;
  if(!flag[nxt] && !vis[nxt]){
   dfs1(nxt);
   maks[pos]=max(maks[pos],sz[nxt]);
   sz[pos]+=sz[nxt];
  }
 }
 sz[pos]++;
 vis[pos]=0;
}



void dfs3(int pos,int dep,int dis){ //trying to match with left subtree
 vis[pos]=1;
 ans=min(ans,dep+match[k-dis]);
 lol.pb(mp(dis,dep));
 masuk.pb(dis);
 for(int i=0;i<adj[pos].size();i++){
  int nxt=adj[pos][i].fi,ndis=dis+adj[pos][i].se;
  if(!vis[nxt] && !flag[nxt] && ndis<=k)
   dfs3(nxt,dep+1,ndis);
 }
 vis[pos]=0;
}



int main(){
 SYNC;
 cin>>n>>k;
 for(int i=1;i<=k;i++) match[i]=INF;
 for(int i=0;i<n-1;i++){
  cin>>a>>b>>d;
  adj[a].pb(mp(b,d));
  adj[b].pb(mp(a,d));
 }
 q.push(0);
 int tot=0;
 while(!q.empty()){
  int pos=q.front();
  q.pop();
  tot++;
  //assert(tot<=n);
  In.clear();
  dfs1(pos);
  int st=pos,ma=INF;
  for(int i=0;i<In.size();i++){
   int now=In[i];
   maks[now]=max(maks[now],(int)In.size()-sz[now]);
   if(maks[now] < ma)
    ma=maks[now],st=now;
  }
  flag[st]=1;
  match[0]=0;
  masuk.clear();
  for(int i=0;i<adj[st].size();i++){
   int nxt=adj[st][i].fi,dis=adj[st][i].se;
   if(!flag[nxt] && dis<=k){
    lol.clear();
    dfs3(nxt,1,dis);
    for(int j=0;j<lol.size();j++)
     match[lol[j].fi]=min(match[lol[j].fi],lol[j].se);
   } 
  }
  for(int i=0;i<masuk.size();i++)
   match[masuk[i]]=INF;
  for(int i=0;i<adj[st].size();i++){
   int nxt=adj[st][i].fi;
   if(!flag[nxt]) q.push(nxt);
  }
  //cout<<st<<" "<<ans<<"\n"; 
  //for(int i=0;i<In.size();i++)
   //cout<<In[i]<<" ";
  //cout<<"\n";   
 }
 //assert(tot==n);
 if(ans==INF) ans=-1;
 cout<<ans<<"\n";
 //puts("ganteng");
 return 0;
}

