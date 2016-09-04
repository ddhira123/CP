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
#define MOD 1000000007
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

inline void add(int &x,int y){
 x+=y;
 if(x>=MOD) x-=MOD;
}

bool vis[8][80000];
int dp[8][80000];
bool flag[8][8];
int tc,n,m;
int a,b,k;
queue<pii> q;
int prev_mask[8],now_mask;
int po[10];

void dfs(int row,int col,int prev,int mask){
 if(col>m){
  add(dp[row][mask],dp[row-1][now_mask]);
  if(!vis[row][mask])
   vis[row][mask]=1,q.push(mp(row,mask));
 }
 else{
  if(flag[row][col])
   dfs(row,col+1,0,mask);
  else{
   for(int i=1;i<=4;i++)
    if(i!=prev && i!=prev_mask[col])
     dfs(row,col+1,i,mask+i*po[col]);
  } 
 }
}

inline int DP(){
 int ans=0;
 vis[0][0]=1;
 dp[0][0]=1;
 q.push(mp(0,0));
 while(!q.empty()){
  int r=q.front().fi;
  now_mask=q.front().se;
  q.pop();
  if(r>n)
   add(ans,dp[r][now_mask]);
  else{
   int tmp=now_mask;
   for(int i=0;i<=m;i++)
    prev_mask[i]=tmp%5,tmp/=5;
   dfs(r+1,0,0,0); 
  }
  vis[r][now_mask]=0;
  dp[r][now_mask]=0; 
 }
 return ans;
}

int main(){
 SYNC;
 po[0]=1;
 for(int i=1;i<=8;i++)
  po[i]=po[i-1]*5;
 cin>>tc;
 for(int t=1;t<=tc;t++){
  memset(flag,0,sizeof flag);
  cin>>n>>m;
  cin>>k;
  while(k--){
   cin>>a>>b;
   flag[a][b-1]=1;
  }
  cout<<"Case "<<t<<": "<<DP()<<"\n";
 }
 //puts("ganteng");
 return 0;
}

