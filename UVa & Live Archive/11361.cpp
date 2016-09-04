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

int dp[11][91][91][2];
int po[11];
int tc,k,a,b;
int arr[11];

int add(int x,int y){
 x+=y;
 while(x>=k) x-=k;
 return x;
}

int solve(int idx,int sum,int dig,int below){
 if(idx==-1)
  return (sum==0 && dig==0);
 int &ret=dp[idx][sum][dig][below];
 if(ret!=-1) return ret;
 ret=0;
 int tot=0;
 if(below) 
  for(int i=0;i<=9;i++){
   ret+=solve(idx-1,add(sum,tot),add(dig,i),1);
   tot=add(tot,po[idx]);
  }
 else
  for(int i=0;i<=arr[idx];i++){
   ret+=solve(idx-1,add(sum,tot),add(dig,i),(i<arr[idx]));
   tot=add(tot,po[idx]);
  } 
 //cout<<idx<<" "<<sum<<" "<<dig<<" "<<below<<" "<<ret<<"\n"; 
 return ret; 
}

int calc(int x){
 if(x==0 || k>90) return 1;
 int it=0;
 po[0]=1;
 arr[0]=0;
 while(x){
  arr[it]=x%10;
  x/=10;
  if(it) po[it]=(10*po[it-1])%k;
  for(int i=0;i<k;i++)
   for(int j=0;j<k;j++)
    dp[it][i][j][0]=dp[it][i][j][1]=-1;
  it++;
 }
 return solve(it-1,0,0,0);
}

int main(){
 SYNC;
 cin>>tc;
 while(tc--){
  cin>>a>>b>>k;
  //cout<<calc(b)<<" "<<calc(a-1)<<"\n";
  cout<<calc(b)-calc(a-1)<<"\n";
 }
 //puts("ganteng");
 return 0;
}

