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

bool valid[505][505],valid2[505][505];
bool vis[505];
int arr[505];
int dp[505],dp2[505][505];
int sum[505][505];
int minkiri[505],minkanan[505];
int n;

void Make(){
 for(int i=1;i<=n;i++){
  memset(vis,0,sizeof vis);
  for(int j=i;j<=n;j++)
   if(!vis[ arr[j] ])
    vis[ arr[j] ]=valid2[i][j]=1;
   else{
    for(int k=j;k<=n;k++)
     valid2[i][k]=0;
    break; 
   } 
 }
 for(int i=1;i<=n;i++){
  int maks=0;
  for(int j=i;j<=n;j++)
   if(!valid2[i][j]) valid[i][j]=0;
   else maks=max(maks,arr[j]),valid[i][j]=(maks == j-i+1);
 }
}


void Compute(){
 Make();
 
 for(int i=1;i<=n;i++){
  for(int j=1;j<=500;j++)
   sum[i][j]=sum[i-1][j];
  for(int j=arr[i];j<=500;j++)
   sum[i][j]++; 
 }
 
 for(int i=1;i<=n;i++)
  dp2[i][i]=0;
 for(int gap=1;gap<n;gap++)
  for(int i=1;i+gap<=n;i++){
   int j=i+gap;
   dp2[i][j]=INF;
   if(!valid2[i][j]) continue;
   int &ret=dp2[i][j];
   minkiri[i-1]=minkanan[j+1]=INF;
   for(int k=i;k<=j;k++)
    minkiri[k]=min(arr[k],minkiri[k-1]);
   for(int k=j;k>=i;k--)
    minkanan[k]=min(arr[k],minkanan[k+1]);
   for(int k=i;k<j;k++){
    int mins1=minkiri[k],mins2=minkanan[k+1];
    int tmp=dp2[i][k] + dp2[k+1][j];
    int tmp2=j-k + k-i+1;
    if(mins1  < mins2) tmp2 -= (sum[k][mins2-1] - sum[i-1][mins2-1]);
    else               tmp2 -= (sum[j][mins1-1] - sum[k][mins1-1]);
    ret=min(ret,tmp+tmp2);
   }  
  } 
}

int solve(int pos){
 int &ret=dp[pos];
 if(ret!=-1) return ret;
 ret=INF;
 for(int i=pos;i<=n;i++)
  if(valid[pos][i]) ret=min(ret,dp2[pos][i] + solve(i+1));
 return ret; 
}

int main(){
 while(scanf("%d",&n)==1){
  for(int i=1;i<=n;i++)
   dp[i]=-1,scanf("%d",&arr[i]);
  Compute();
  int ret=solve(1);
  if(ret==INF) puts("impossible");
  else printf("%d\n",ret); 
 }
 //puts("ganteng");
 return 0;
}

