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

double dp[2][105][105];
pii arr[105];
double dist[105][105];
int n,b1,b2,tc;

//0 -> b1 dari kiri ke kanan
//1 -> b1 dari kanan ke kiri
double solve(int op,int l,int r){
 if(l==n-1 || r==n-1) return dist[l][r];
 double &ret=dp[op][l][r];
 if(ret > -0.5) return ret;
 int m=max(l,r)+1;
 double tmp=dist[l][m]+solve(op,m,r),tmp2=dist[r][m]+solve(op,l,m);
 if((op==0 && b1==m) || (op==1 && b2==m))
  return ret=tmp;
 else if((op==0 && b2==m) || (op==1 && b1==m))
  return ret=tmp2;
 else
  return ret=min(tmp,tmp2); 
}

inline void Res(int op){
 vector<int> lr,rl;
 lr.pb(0);
 rl.pb(0);
 int l=0,r=0;
 for(int m=1;m<n;m++){
 double tmp=dist[l][m]+solve(op,m,r),tmp2=dist[r][m]+solve(op,l,m);
 if((op==0 && b1==m) || (op==1 && b2==m))
  lr.pb(m),l=m;
 else if((op==0 && b2==m) || (op==1 && b1==m))
  rl.pb(m),r=m;
 else if(tmp + EPS < tmp2)
  lr.pb(m),l=m;
 else
  rl.pb(m),r=m;   
 }
 if(rl.size()>=2 && rl[1]==1) swap(lr,rl);
 printf("%d",lr[0]);
 for(int i=1;i<lr.size();i++)
  printf(" %d",lr[i]);
 for(int i=rl.size()-1 ; i>=0 ; i--)
  printf(" %d",rl[i]);
 puts("");  
}

int main(){
 scanf("%d %d %d",&n,&b1,&b2);
 while(n|b1|b2){
  for(int i=0;i<n;i++)
   scanf("%d %d",&arr[i].fi,&arr[i].se);
  for(int i=0;i<n;i++)
   for(int j=0;j<n;j++)
    dist[i][j]=hypot(arr[i].fi-arr[j].fi,arr[i].se-arr[j].se),dp[0][i][j]=dp[1][i][j]=-1.0;
  double tmp=solve(0,0,0),tmp2=solve(1,0,0),ans;
  int op;
  if(tmp + EPS < tmp2) ans=tmp,op=0;
  else                 ans=tmp2,op=1;   
  printf("Case %d: %.2lf\n",++tc,ans);
  Res(op);  
  scanf("%d %d %d",&n,&b1,&b2);
 }
 //puts("ganteng");
 return 0;
}

