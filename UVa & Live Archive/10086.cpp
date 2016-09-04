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

int dp[35][305];
int t1,t2,n,m;
int cost[2][35][305],jum[35],site[35];

int solve(int pos,int left){
 if(pos>n){
  if(left>0) return INF;
  return 0;
 }
 else if(dp[pos][left]!=-1) return dp[pos][left];
 else{
  int ret=INF;
  for(int i=min(left,site[pos]);i>=0;i--){
   int tmp=cost[0][pos][i]+cost[1][pos][site[pos]-i]+solve(pos+1,left-i);
   //printf("POS %d LEFT %d USE %d SUM %d\n",pos,left,i,tmp);
   ret=min(ret,tmp);
   }
  //printf("%d %d -> %d\n",pos,left,ret); 
  return dp[pos][left]=ret;
 }
}

inline void traverse(){
 int left=t1;
 for(int i=1;i<=n;i++){
  bool found=0;
  for(int j=min(left,site[i]);j>=0;j--)
   if(solve(i,left)==cost[0][i][j]+cost[1][i][site[i]-j]+solve(i+1,left-j)){
    //printf("%d %d %d\n",i,left,solve(i,left));
    jum[i]=j;
    left-=j;
    found=1;
    break;
   }
  //assert(found); 
 }
}

int main(){
 t1=io(),t2=io();
 while(t1|t2){
  n=io();
  for(int i=1;i<=n;i++){
   site[i]=io();
   for(int j=0;j<2;j++)
    for(int k=1;k<=site[i];k++)
     cost[j][i][k]=io();//printf("%d %d %d -> %d\n",j,i,k,cost[j][i][k]);
   for(int j=0;j<=t1;j++)
    dp[i][j]=-1;  
  }
  printf("%d\n",solve(1,t1));
  traverse();
  printf("%d",jum[1]);
  for(int i=2;i<=n;i++)
   printf(" %d",jum[i]);
  printf("\n\n");   
  t1=io(),t2=io();
 }
 //puts("ganteng");
 return 0;
}

