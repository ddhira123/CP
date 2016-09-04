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
#define g getchar_unlocked
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL
#define DEBUG puts("DEBUG")


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

int tc,n,t;
pii dp[55][9005];
int arr[55],tot;

pii solve(int pos,int left){
 if(pos==n){
  if(left) return mp(1,678);
  else     return mp(0,0); 
 }
 else if(dp[pos][left].fi!=-1) return dp[pos][left];
 else{
  pii op1=mp(-1,-1),op2=op1;
  op1=solve(pos+1,left);
  if(left>=arr[pos])
   op2=solve(pos+1,left-arr[pos]),op2.se+=arr[pos],op2.fi++;
  if(op1.fi>op2.fi)
   dp[pos][left]=op1;
  else if(op1.fi < op2.fi)
   dp[pos][left]=op2;
  else
   dp[pos][left]=mp(op1.fi,max(op1.se,op2.se));
  return dp[pos][left];    
 }
}

int main(){
 tc=io();
 for(int T=1;T<=tc;T++){
  tot=0;
  n=io(),t=io();
  for(int i=0;i<n;i++)
   arr[i]=io(),tot+=arr[i];
  pii ans; 
  if(tot<t)
   ans=mp(n+1,tot+678);
  else{
   for(int i=0;i<n;i++)
    for(int j=0;j<=t;j++)
     dp[i][j].fi=-1;
   ans=solve(0,t);  
  }
  printf("Case %d: %d %d\n",T,ans.fi,ans.se); 
 }
 //puts("ganteng");
 return 0;
}

