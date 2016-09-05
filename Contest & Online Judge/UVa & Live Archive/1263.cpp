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
#define N 2005

vector<int> adj[N];
int x[N],y[N],d[N];
int num[N],low[N],flag[N];
bool can[N];
vector<int> v;
int ctr,ans;
int tc,n;

void Tarjan(int cur){
 flag[cur]=1;
 can[ctr]=0;
 num[cur]=low[cur]=ctr++;
 v.pb(cur);
 for(int i=0;i<adj[cur].size();i++){
  int nxt=adj[cur][i];
  if(flag[nxt]==-1) Tarjan(nxt);
  if(flag[nxt]==1)  low[cur]=min(low[cur],low[nxt]);
 }

 if(num[cur]==low[cur]){
  ans++;
  can[low[cur]]=1;
  while(1){
   int nxt=v.back(); v.pop_back();
   flag[nxt]=0,low[nxt]=low[cur];
   //cout<<nxt<<" ";
   if(nxt==cur){
    //cout<<"\n";
    break;
   }
  }
 }
}

int main(){
 SYNC;
 cin>>tc;
 while(tc--){
  cin>>n;
  ctr=ans=0;
  for(int i=0;i<n;i++){
   adj[i].clear(); flag[i]=-1;
   cin>>x[i]>>y[i]>>d[i];
   for(int j=0;j<i;j++){
    if(abs(x[i]-x[j])<=(d[i]+1)/2 && abs(y[i]-y[j])<=(d[i]+1)/2)
     adj[i].pb(j);
    if(abs(x[i]-x[j])<=(d[j]+1)/2 && abs(y[i]-y[j])<=(d[j]+1)/2)
     adj[j].pb(i); 
   }
  }
  for(int i=0;i<n;i++)
   if(flag[i]==-1)
    Tarjan(i);
  for(int i=0;i<n;i++)
   for(int j=0;j<adj[i].size();j++){
    int nxt=adj[i][j];
    //cout<<i<<" "<<nxt<<"\n";
    if(low[nxt]!=low[i]){
     ans-=can[low[nxt]];
     can[low[nxt]]=0;
    }
   }
  cout<<ans<<"\n";   
 }
 //puts("ganteng");
 return 0;
}

