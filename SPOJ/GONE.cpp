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

int dp[11][91][2];
int arr[11];
int a,b,tc;
bool flag[91];

inline void Generate(){
 flag[0]=flag[1]=1;
 for(int i=2;i<=90;i++)
  if(!flag[i])
   for(int j=i;j<=90/i;j++)
    flag[j*i]=1;
}

int solve(int idx,int sum,int below){
 if(idx==-1)
  return !flag[sum];
 int &ret=dp[idx][sum][below];
 if(ret!=-1) return ret;
 ret=0;
 if(below)
  for(int i=0;i<=9;i++)
   ret+=solve(idx-1,sum+i,1);
 else
  for(int i=0;i<=arr[idx];i++)
   ret+=solve(idx-1,sum+i,(i<arr[idx]));
 return ret;     
}

inline int calc(int x){
 arr[0]=0;
 int it=0;
 while(x){
  arr[it]=x%10;
  x/=10;
  for(int i=0;i<=90;i++)
   dp[it][i][0]=dp[it][i][1]=-1;
  it++;
 }
 return solve(it-1,0,0);
}

int main(){
 SYNC;
 Generate();
 cin>>tc;
 while(tc--){
  cin>>a>>b;
  cout<<calc(b)-calc(max(a-1,0))<<"\n";
 }
 //puts("ganteng");
 return 0;
}

