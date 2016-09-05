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
vector<pair<int,pss> > v[2];
vector<int> adj[505];
char x;
pair<int,pss> tmp;
int tc,n;
int match[505];
bool vis[505];

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

inline int MCBM(){
 for(int i=0;i<v[1].size();i++)
  match[v[0].size()+i]=-1;
 int ans=0; 
 for(int i=0;i<v[0].size()&&ans<v[1].size();i++){
  for(int j=0;j<v[0].size();j++)
   vis[j]=0;
  ans+=Augment(i); 
 } 
 return ans;
}

int main(){
 SYNC;
 cin>>tc;
 while(tc--){
  v[0].clear(),v[1].clear();
  cin>>n;
  for(int i=0;i<n;i++){
   cin>>tmp.fi>>x>>tmp.se.fi>>tmp.se.se;
   if(x=='M') v[0].pb(tmp);
   else       v[1].pb(tmp);
  }
  for(int i=0;i<v[0].size();i++){
   adj[i].clear();
   for(int j=0;j<v[1].size();j++){
    pair<int,pss> dum,dum2;
    dum=v[0][i];
    dum2=v[1][j];
    if(abs(dum.fi-dum2.fi)<=40 && dum.se.fi==dum2.se.fi && dum.se.se!=dum2.se.se)
     adj[i].pb(v[0].size()+j);
   }
  }
  cout<<n-MCBM()<<"\n";
 }
 //puts("ganteng");
 return 0;
}

