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

int n,counter,q;
int id[100005];
vector<int> v[100005],adj[100005];
LL arr[100005],sub[100005],all;
char op;
int x;

void dfs(int pos){
 id[pos]=++counter;
 v[pos].pb(id[pos]);
 for(int i=0;i<adj[pos].size();i++){
  int nxt=adj[pos][i];
  dfs(nxt);
  sub[pos]+=sub[nxt];
  v[pos].pb(counter);
 }
 sub[pos]+=arr[pos];
}

int main(){
 n=io();
 for(int i=1;i<=n;i++) 
  arr[i]=io(),all+=arr[i];
 for(int i=2;i<=n;i++){
  x=io();
  adj[x].pb(i);
 }
 dfs(1);
 int root=1; 
 q=io();
 while(q--){
  op=g(); x=io();
  if(op=='R') root=x;
  else{
   if(root==x) printf("%lld\n",all);
   else if(id[root] < v[x][0] || id[root] > v[x][v[x].size()-1])
    printf("%lld\n",sub[x]);
   else{
    int idx=lower_bound(v[x].begin(),v[x].end(),id[root])-v[x].begin();
    idx--;
    printf("%lld\n",all-sub[adj[x][idx]]);
   } 
  }
 }
 //puts("ganteng");
 return 0;
}
