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
#define MOD 1000000000LL
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

struct Node{
 LL Size;
 LL Total;
 LL Path;
};

Node Tree[100005];
map<pii,int> ma;
int n;
pii arr[100005];
vector<int> adj[100005];

void DFS(int now,int prev){
 Tree[now].Total = Tree[now].Path = 0;
 LL awal = Tree[now].Size;
 for(int i = 0 ; i < adj[now].size() ; i++){
  int nxt = adj[now][i];
  if(nxt == prev) continue;
  DFS(nxt,now);
  Tree[now].Total = (Tree[now].Total + Tree[nxt].Total + awal*(Tree[nxt].Size + Tree[nxt].Path))%MOD;
  Tree[now].Path =  (Tree[now].Path + (Tree[nxt].Size + Tree[nxt].Path)) % MOD;
  Tree[now].Size += Tree[nxt].Size;
 }
 
 //printf("SUB %d SIZE %lld CURRENT %lld\n",now,Tree[now].Size,Tree[now].Total);
 
 LL add = Tree[now].Size - awal;
 for(int i = 0 ; i < adj[now].size() ; i++){
  int nxt = adj[now][i];
  if(nxt == prev) continue;
  LL bef = Tree[now].Total;
  Tree[now].Total = (Tree[now].Total + (add - Tree[nxt].Size)*(Tree[nxt].Path + Tree[nxt].Size)) % MOD;
  //printf("AFTER ADD %d -> %lld\n",nxt,Tree[now].Total - bef);
 }
 
}

void Read(){
 scanf("%d",&n);
 for(int i = 0 ; i < n ; i++)
  scanf("%d %d",&arr[i].fi,&arr[i].se);
}

void Process(){
 LL ans = 0;
 for(int i = 0 ; i < 2 ; i++){
  sort(arr,arr+n);
  ma.clear();
  int it = 0;
  //printf("NOW %d\n",i);
  for(int j = 0 ; j < n ;){
   int k = j;
   int last = arr[j].se-1;
   adj[it].clear();
   while(k < n && arr[k].fi == arr[j].fi && arr[k].se == last + 1){
    ma[ arr[k] ] = it;
    //printf("%d %d\n",arr[k].fi,arr[k].se);
    last = arr[k].se;
    k++;
   }
   //puts("STOP");
   Tree[it].Size = k-j;
   it++;
   j = k;
  }
  for(int j = 0 ; j < n ; j++){
   int id,id2;
   id = ma[ arr[j] ];
   if(ma.count(mp(arr[j].fi-1,arr[j].se))){
    id2 = ma[mp(arr[j].fi-1,arr[j].se)];
    adj[id].pb(id2);
    adj[id2].pb(id);
   } 
  }
  
  for(int j = 0 ; j < it ; j++){
   sort(adj[j].begin(),adj[j].end());
   adj[j].erase(unique(adj[j].begin(),adj[j].end()) , adj[j].end());
   //printf("ADJ %d ->",j);
   //for(int k = 0 ; k < adj[j].size() ; k++)
    //printf(" %d",adj[j][k]);
   //puts(""); 
  }
  
  DFS(0,-1);
  ans += Tree[0].Total;
  for(int j = 0 ; j < n ; j++)
   swap(arr[j].fi,arr[j].se);
 }
 
 printf("%lld\n",ans%MOD);
}

int main(){
 Read();
 Process();
 //puts("ganteng");
 return 0;
}

