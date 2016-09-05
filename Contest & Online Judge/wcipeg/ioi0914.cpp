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
#define INF 2000000000
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

int dp[52][52][52][52];
int pref[52][52];
int n,m;

int solve(int atas,int bawah,int kiri,int kanan){
 if(atas==bawah && kiri==kanan) return 0;
 int &ret=dp[atas][bawah][kiri][kanan];
 if(ret != -1) return ret;
 ret=INF;
 for(int i=atas;i<bawah;i++)
  ret=min(ret,solve(atas,i,kiri,kanan) + solve(i+1,bawah,kiri,kanan));
 for(int i=kiri;i<kanan;i++)
  ret=min(ret,solve(atas,bawah,kiri,i) + solve(atas,bawah,i+1,kanan)); 
 ret+=pref[bawah][kanan] - pref[bawah][kiri-1] - pref[atas-1][kanan] + pref[atas-1][kiri-1];
 return ret;
}

int main(){
 SYNC;
 memset(dp,-1,sizeof dp);
 cin>>n>>m;
 for(int i=1;i<=n;i++)
  for(int j=1;j<=m;j++){
   cin>>pref[i][j];
   pref[i][j]+=pref[i-1][j]+pref[i][j-1];
   pref[i][j]-=pref[i-1][j-1];
  }
 cout<<solve(1,n,1,m)<<"\n";
 //puts("ganteng");
 return 0;
}

