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

int arr[2005];
int n,p,q;
int dp[2005][2005];

int get(int x,int y,int w){
 if(x==-1 || y==-1) return -1;
 int it=dp[x][y]+1;
 int it2=it;
 while(it2 < n && arr[it2]-arr[it]<=w) it2++;
 return it2-1;
}

bool valid(int x){
 //memset(dp,0,sizeof dp);
 //if(p+q>=n) return 1;
 dp[0][0]=-1;
 for(int i=0;i<=min(n,p);i++)
  for(int j=0;j<=min(n,q);j++)
    dp[i][j]=max(get(i-1,j,x-1),get(i,j-1,2*x-1));
 //cout<<x<<" "<<dp[p][q]<<"\n";   
 return dp[min(n,p)][min(n,q)]==n-1;   
}

int main(){
 SYNC;
 cin>>n>>p>>q;
 for(int i=0;i<n;i++) cin>>arr[i];
 sort(arr,arr+n);
 //cout<<valid(4)<<"\n";
 int lo=1,hi=INF;
 while(lo<hi){
  int mi=(lo+hi)>>1;
  if(valid(mi)) hi=mi;
  else lo=mi+1;
 }
 cout<<lo<<"\n";
 //puts("ganteng");
 return 0;
}

