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

LL dp[20][20];
int arr[20];
int tc;
LL a,b;

inline void Precompute(){
 dp[0][0]=1;
 for(int i=0;i<18;i++)
  for(int j=0;j<=15;j++)
   for(int k=0;k<=9;k++)
    dp[i+1][j^k]+=dp[i][j];
}

inline LL calc(LL x){
 int it=0;
 //printf("NOW -> %lld\n",x);
 while(x){
  arr[it]=x%10LL;
  x/=10LL;
  it++;
 }
 int mask=0;
 LL ans=0;
 for(int i=it-1;i>=0;i--){
  for(int j=0;j<arr[i];j++)
   ans+=dp[i][mask^j];
  mask^=arr[i];
 }
 if(mask==0) ans++;
 //printf("%lld\n",ans);
 return ans;
}

int main(){
 Precompute();
 scanf("%d",&tc);
 while(tc--){
  scanf("%lld %lld",&a,&b);
  LL bob=calc(b)-calc(a-1);
  LL alice=(b-a+1) - bob;
  printf("%lld %lld\n",alice,bob);
 }
 //puts("ganteng");
 return 0;
}
