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

int dp[2][4][4][4][4];
string s;
int tmp[3];
int n;
queue<pair<pii,pair<pii,int> > > q;
bool vis[2][4][4][4][4];

int Score(int a,int b,int c){
 tmp[0]=a;tmp[1]=b;tmp[2]=c;
 if(tmp[1] < tmp[0]) swap(tmp[1],tmp[0]);
 if(tmp[2] < tmp[0]) swap(tmp[2],tmp[0]);
 if(tmp[2] < tmp[1]) swap(tmp[1],tmp[2]);
 int tot=(tmp[0]>0);
 tot+=(tmp[1]>tmp[0]);
 tot+=(tmp[2]>tmp[1]);
 return tot;
}

int main(){
 SYNC;
 cin>>n;
 cin>>s;
 int ans=0;
 vis[0][0][0][0][0]=1;
 q.push(mp(mp(0,0),mp(mp(0,0),0)));
 while(!q.empty()){
  int i=q.front().fi.fi,j=q.front().fi.se,k=q.front().se.fi.fi;
  int l=q.front().se.fi.se,m=q.front().se.se;
  q.pop();
  if(i<n){
   int now;
   if(s[i]=='M') now=1;
   else if(s[i]=='F') now=2;
   else now=3;
   dp[(i&1)^1][k][now][l][m]=max(dp[(i&1)^1][k][now][l][m],dp[i&1][j][k][l][m]+Score(j,k,now));
   dp[(i&1)^1][j][k][m][now]=max(dp[(i&1)^1][j][k][m][now],dp[i&1][j][k][l][m]+Score(l,m,now));
   if(!vis[(i&1)^1][k][now][l][m]) vis[(i&1)^1][k][now][l][m]=1,q.push(mp(mp(i+1,k),mp(mp(now,l),m)));
   if(!vis[(i&1)^1][j][k][m][now]) vis[(i&1)^1][j][k][m][now]=1,q.push(mp(mp(i+1,j),mp(mp(k,m),now)));
  }
  else
   ans=max(ans,dp[i&1][j][k][l][m]);
  vis[i&1][j][k][l][m]=0;
  dp[i&1][j][k][l][m]=0;
 }
 cout<<ans<<"\n";     
 //puts("ganteng");
 return 0;
}

