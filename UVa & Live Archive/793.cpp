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

int par[100005];
string x;
int tc,n;

int finds(int y){
 return y==par[y] ? y : par[y]=finds(par[y]);
}

inline bool issame(int a,int b){
 return finds(a)==finds(b);
}

inline void uni(int a,int b){
 if(!issame(a,b))
  par[finds(a)]=finds(b);
}



int main(){
 SYNC;
 cin>>tc;
 getline(cin,x);
 getline(cin,x);
 while(tc--){
  cin>>n;
  for(int i=0;i<=n;i++)
   par[i]=i;
  getline(cin,x);
  getline(cin,x);
  int ans1=0,ans2=0;
  while(x!=""){
   int it=0;
   int tmp[2]={0,0};
   int len=x.length();
   for(int i=2;i<len;i++)
    if(x[i]==' ') it++;
    else tmp[it]=10*tmp[it]+x[i]-'0';
   if(x[0]=='c') uni(tmp[0],tmp[1]);
   else if(issame(tmp[0],tmp[1])) ans1++;
   else                           ans2++;
   getline(cin,x);
  }
  cout<<ans1<<","<<ans2<<"\n";
  if(tc)
   cout<<"\n";
 }
 //puts("ganteng");
 return 0;
}

