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

int tc,n,a,b;
pss tmp;
vector<pss> dog,cat;
vector<int> adj[505];
int match[505];
bool vis[505];

inline void Build_Graph(){
 for(int i=0;i<cat.size();i++){
  adj[i].clear();
  for(int j=0;j<dog.size();j++)
   if(cat[i].fi==dog[j].se || cat[i].se==dog[j].fi)
    adj[i].pb(cat.size()+j);
 }
}

int Augment(int pos){
 if(vis[pos]) return 0;
 vis[pos]=1;
 for(int i=0;i<adj[pos].size();i++){
  int nxt=adj[pos][i];
  if(match[nxt]==-1 || Augment(match[nxt])){
   match[nxt]=pos;
   return 1;
  }
 }
 return 0;
}

int MCBM(){
 for(int i=0;i<dog.size();i++)
  match[cat.size()+i]=-1;
 int ret=0; 
 for(int i=0;i<cat.size();i++){
  for(int j=0;j<cat.size();j++)
   vis[j]=0;
  ret+=Augment(i); 
 } 
 return ret;
}

int main(){
 SYNC;
 cin>>tc;
 while(tc--){
  dog.clear(),cat.clear();
  cin>>a>>b>>n;
  for(int i=0;i<n;i++){
   cin>>tmp.fi>>tmp.se;
   if(tmp.fi[0]=='C')
    cat.pb(tmp);
   else
    dog.pb(tmp); 
  }
  Build_Graph();
  cout<<n-MCBM()<<"\n";
 }
 //puts("ganteng");
 return 0;
}

