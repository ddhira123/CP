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

int n,md;
string s;

int dp[2][5][5][5];
int maks[1000005],mini[1000005];
int sum;

inline int add(int &x,int y){
 x+=y;
 if(x>=md) x-=md;
}

int main(){
 SYNC;
 cin>>n>>md;
 cin>>s;
 sum=2;   
 for(int i=0;i<n;i++){
  if(s[i]=='P') sum++;
  else sum--;
  maks[i]=max(sum,2);
  mini[i]=min(sum,2);
  if(i){
   maks[i]=max(maks[i],maks[i-1]);
   mini[i]=min(mini[i],mini[i-1]);
  }
 }
 int bit=(n&1);
 for(int j=0;j<=4;j++)
  for(int k=max(j,2);k<=4;k++)
   for(int l=max(k-2,0);l<=min(2,j);l++)
    dp[bit][j][k][l]=1; 
 int ans=0;

 for(int i=n-1;i>=0;i--){
  bit=i&1;
  if(s[i]=='L') sum++;
  else{
   int tmp=0;
   if(sum>1){
    if(i)
     tmp=dp[bit^1][sum-2][max(maks[i-1],sum-2)][min(mini[i-1],sum-2)];
    else
     tmp=dp[bit^1][sum-2][max(2,sum-2)][min(2,sum-2)]; 
   }
   //cout<<i<<" "<<tmp<<" "<<sum-2<<"\n";
   add(ans,tmp);
   sum--;
  }  
  //cout<<i<<" "<<sum<<" "<<maks[i]<<" "<<mini[i]<<"\n";
 for(int j=0;j<=4;j++)
  for(int k=max(j,2);k<=4;k++)
   for(int l=max(k-2,0);l<=min(2,j);l++){
     dp[bit][j][k][l]=0;
     if(j)   add(dp[bit][j][k][l],dp[bit^1][j-1][k][min(l,j-1)]);
     if(j<4) add(dp[bit][j][k][l],dp[bit^1][j+1][max(j+1,k)][l]);
    }   
 }
 //cout<<dp[bit][1][2][1]+dp[bit][3][3][2]<<"\n";
 add(ans,1);
 cout<<ans<<"\n";   
 //puts("ganteng");
 return 0;
}

