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
#define INF 2000000000
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

int sum[255],prefix[255];
int dp[255][255],Knuth[255][255];
int n;

int main(){
 SYNC;
 while(cin>>n){
  for(int i=1;i<=n;i++)
   cin>>prefix[i],prefix[i]+=prefix[i-1];
  for(int i=0;i<=n;i++)
   Knuth[i][i+1]=i,dp[i][i+1]=0;
  for(int gap=2;gap<=n+1;gap++)
   for(int i=0;i+gap<=n+1;i++){
    int j=i+gap;
    int sum=prefix[j-1]-prefix[i];
    int le=Knuth[i][j-1],rig=Knuth[i+1][j];
    dp[i][j]=INF;
    for(int k=le;k<=rig;k++){
     int tmp=sum-(prefix[k]-prefix[k-1])+dp[i][k]+dp[k][j];
     if(tmp<dp[i][j])
      dp[i][j]=tmp,Knuth[i][j]=k;
    }
   }
  cout<<dp[0][n+1]<<"\n";   
 } 
 //puts("ganteng");
 return 0;
}

