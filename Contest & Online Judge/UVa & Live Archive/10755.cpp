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

LL sum[25][25][25];
int tc,a,b,c;

LL get(int i,int j,int k,int l,int m){
 LL ret=sum[j][l][m];
 ret-=sum[i-1][l][m];
 ret-=sum[j][k-1][m];
 ret+=sum[i-1][k-1][m];
 return ret;
}

int main(){
 SYNC;
 cin>>tc;
 while(tc--){
  cin>>a>>b>>c;
  for(int i=1;i<=a;i++)
   for(int j=1;j<=b;j++)
    for(int k=1;k<=c;k++){
     cin>>sum[i][j][k];
     sum[i][j][k]+=sum[i-1][j][k];
     sum[i][j][k]+=sum[i][j-1][k];
     sum[i][j][k]+=sum[i][j][k-1];
     sum[i][j][k]-=sum[i-1][j-1][k];
     sum[i][j][k]-=sum[i-1][j][k-1];
     sum[i][j][k]-=sum[i][j-1][k-1];
     sum[i][j][k]+=sum[i-1][j-1][k-1];
    }
  //cout<<sum[a][b][c]<<"\n";  
  LL ans=-INFLL;
  for(int i=1;i<=a;i++)
   for(int j=i;j<=a;j++)
    for(int k=1;k<=b;k++)
     for(int l=k;l<=b;l++){
      LL cnt=0;
      for(int m=1;m<=c;m++){
       cnt+=get(i,j,k,l,m);
       cnt-=get(i,j,k,l,m-1);
       ans=max(ans,cnt);
       cnt=max(cnt,0LL);
      }
     }  
  cout<<ans<<"\n";   
  if(tc) cout<<"\n";
 }
 //puts("ganteng");
 return 0;
}

