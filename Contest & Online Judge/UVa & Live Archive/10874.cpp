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

LL dp[20005][2];
LL arr[20005][2];
int n;

int main(){
 n=io();
 arr[0][0]=arr[0][1]=1;
 while(n){
  for(int i=1;i<=n;i++)
   arr[i][0]=io(),arr[i][1]=io();
  dp[n+1][0]=dp[n+1][1]=0;
  arr[n+1][0]=arr[n+1][1]=n;
  for(int i=n;i>=0;i--)
   for(int j=0;j<2;j++)
    dp[i][j]=abs(arr[i][0]-arr[i][1])+min(abs(arr[i][1-j]-arr[i+1][0])+dp[i+1][0],abs(arr[i][1-j]-arr[i+1][1])+dp[i+1][1]);
  printf("%lld\n",dp[0][0]+(LL)(n-1));   
  n=io();
 }
 //puts("ganteng");
 return 0;
}

