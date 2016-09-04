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
#define MOD 50431
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

int dp[21][1<<10];
string arr[10];
bool vis[21][1<<10];
int tc,n,m;
queue<pii> q;

void dfs(int mask,int nmask,int r,int c){
 if(r==n){
  add(dp[c+1][nmask],dp[c][mask]);
  if(!vis[c+1][nmask])
   vis[c+1][nmask]=1,q.push(mp(c+1,nmask));
 }
 else if( (mask&(1<<r))!=0 || arr[r][c]=='#')
  dfs(mask,nmask,r+1,c);
 else if(arr[r][c]=='R'){
  if(r<n-1 && c<m-1 && (arr[r+1][c]=='R' || arr[r+1][c]=='.') && (mask&(1<<(r+1)))==0 && (arr[r+1][c+1]=='R' || arr[r+1][c+1]=='.')
     && (nmask&  (1<<(r+1)))==0){
      dfs(mask,nmask|(1<<(r+1)),r+2,c);
     }
 }
 else if(arr[r][c]=='G'){
  if(r>0 && c<m-1 && (arr[r][c+1]=='G' || arr[r][c+1]=='.') && (nmask&(1<<r))==0 && 
    (arr[r-1][c+1]=='G' || arr[r-1][c+1]=='.') && (nmask&(1<<(r-1)))==0){
      dfs(mask,nmask|(1<<r)|(1<<(r-1)),r+1,c);
     }
 }
 else if(arr[r][c]=='B'){
  if(r<n-1 && c<m-1 && (arr[r+1][c]=='B' || arr[r+1][c]=='.') && (mask&(1<<(r+1)))==0 && (arr[r][c+1]=='B' || arr[r][c+1]=='.')
     && (nmask&(1<<r))==0){
      dfs(mask,nmask|(1<<r),r+2,c);
     }
 }
 else if(arr[r][c]=='N'){
  if(r<n-1 && c<m-1 && (arr[r][c+1]=='N' || arr[r][c+1]=='.') && (nmask&(1<<r))==0 && 
    (arr[r+1][c+1]=='N' || arr[r+1][c+1]=='.') && (nmask&(1<<(r+1)))==0){
      dfs(mask,nmask|(1<<r)|(1<<(r+1)),r+1,c);
     }
 }
 else if(arr[r][c]=='W'){
  if(r<n-1 && (arr[r+1][c]=='W' || arr[r+1][c]=='.') && (mask&(1<<(r+1)))==0)
   dfs(mask,nmask,r+2,c);
 } 
 else if(arr[r][c]=='P'){
  if(c<m-1 && (arr[r][c+1]=='P' || arr[r][c+1]=='.') && (nmask&(1<<r))==0)
   dfs(mask,nmask|(1<<r),r+1,c);
 }
 else if(arr[r][c]=='L')
  dfs(mask,nmask,r+1,c);
 else{
  if(r<n-1 && c<m-1 && (arr[r+1][c]=='R' || arr[r+1][c]=='.') && (mask&(1<<(r+1)))==0 && (arr[r+1][c+1]=='R' || arr[r+1][c+1]=='.')
     && (nmask&  (1<<(r+1)))==0){
      dfs(mask,nmask|(1<<(r+1)),r+2,c);
     }  
  if(r>0 && c<m-1 && (arr[r][c+1]=='G' || arr[r][c+1]=='.') && (nmask&(1<<r))==0 && 
    (arr[r-1][c+1]=='G' || arr[r-1][c+1]=='.') && (nmask&(1<<(r-1)))==0){
      dfs(mask,nmask|(1<<r)|(1<<(r-1)),r+1,c);
     }     
  if(r<n-1 && c<m-1 && (arr[r+1][c]=='B' || arr[r+1][c]=='.') && (mask&(1<<(r+1)))==0 && (arr[r][c+1]=='B' || arr[r][c+1]=='.')
     && (nmask&(1<<r))==0){
      dfs(mask,nmask|(1<<r),r+2,c);
     }   
  if(r<n-1 && c<m-1 && (arr[r][c+1]=='N' || arr[r][c+1]=='.') && (nmask&(1<<r))==0 && 
    (arr[r+1][c+1]=='N' || arr[r+1][c+1]=='.') && (nmask&(1<<(r+1)))==0){
      dfs(mask,nmask|(1<<r)|(1<<(r+1)),r+1,c);
     }
  if(r<n-1 && (arr[r+1][c]=='W' || arr[r+1][c]=='.') && (mask&(1<<(r+1)))==0)
   dfs(mask,nmask,r+2,c); 
  if(c<m-1 && (arr[r][c+1]=='P' || arr[r][c+1]=='.') && (nmask&(1<<r))==0)
   dfs(mask,nmask|(1<<r),r+1,c);    
  dfs(mask,nmask,r+1,c);             
 }  
}

inline int DP(){
 dp[0][0]=1;
 q.push(mp(0,0));
 vis[0][0]=1;
 while(!q.empty()){
  int cc=q.front().fi,mm=q.front().se;
  q.pop();
  //cout<<cc<<" "<<mm<<" "<<dp[cc][mm]<<"\n";
  if(cc==m) continue;
  dfs(mm,0,0,cc);
  dp[cc][mm]=0;
  vis[cc][mm]=0;
 }
 int ans=dp[m][0];
 dp[m][0]=0;
 vis[m][0]=0;
 return ans;
}

int main(){
 SYNC;
 cin>>tc;
 for(int t=1;t<=tc;t++){
  cin>>n>>m;
  for(int i=0;i<n;i++)
   cin>>arr[i];
  cout<<"Case "<<t<<": "<<DP()<<"\n"; 
 }
 //puts("ganteng");
 return 0;
}

