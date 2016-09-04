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

typedef pair<int,int> pii;
typedef long long LL;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define g getchar_unlocked
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL

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

pair<pii,int> arr[30005];
int tc,n;
int dp[30005];

int main(){
 tc=io();
 for(int t=1;t<=tc;t++){
  n=io();
  for(int i=0;i<n;i++)
   arr[i].fi.fi=io(),arr[i].fi.se=io(),arr[i].se=io();
  sort(arr,arr+n);
  dp[n]=0;
  for(int i=n-1;i>=0;i--){
   dp[i]=dp[i+1];
   int pos=lower_bound(arr+i,arr+n,mp(mp(arr[i].fi.fi+arr[i].fi.se,0),0 ) )-arr;
   dp[i]=max(dp[i],arr[i].se+dp[pos]);
  } 
  printf("Case %d: %d\n",t,dp[0]);
 }
 //puts("ganteng");
 return 0;
}

