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

int tc,n,m,k;
int arr[1005][1005];
int sum[1005][1005];

int area(int lim){
 int ans=0;
 for(int i=1;i<=n;i++){
  vector<pii> v;
  for(int j=1;j<=m;j++){
   sum[i][j]=(arr[i][j] >= lim ? sum[i-1][j] + 1 : 0);
   int pos=j,hi=sum[i][j];
   while(!v.empty() && v.back().fi >= hi){
    pii lol=v.back();
    pos=lol.se;
    ans=max(ans,lol.fi*(j-lol.se));
    v.pop_back();
   }
   ans=max(ans,(j-pos+1)*hi);
   v.pb(mp(hi,pos));
  }
  while(!v.empty()){
   pii lol=v.back();
   v.pop_back();
   ans=max(ans,lol.fi*(m+1-lol.se));
  }
 }
 return ans;
}

int main(){
 tc=io();
 while(tc--){
  n=io(),m=io(),k=io();
  int maks=0,mini=INF;
  for(int i=1;i<=n;i++)
   for(int j=1;j<=m;j++)
    arr[i][j]=io(),mini=min(mini,arr[i][j]),maks=max(maks,arr[i][j]);
  while(mini < maks){
   int mi=(mini+maks+1)>>1;
   if(area(mi) >= k) mini=mi;
   else maks=mi-1;
  }
  printf("%d %d\n",mini,area(mini));  
 }
 //puts("ganteng");
 return 0;
}
