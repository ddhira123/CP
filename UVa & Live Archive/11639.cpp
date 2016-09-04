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

int x[4],y[4],ans1,ans2,ans3;
int tc;

int main(){
 SYNC;
 cin>>tc;
 for(int t=1;t<=tc;t++){
  for(int i=0;i<4;i++)
   cin>>x[i]>>y[i];
  int le=max(x[0],x[2]);
  int rig=min(x[1],x[3]);
  int up=max(y[0],y[2]);
  int down=min(y[1],y[3]);
  if(rig <= le || down<=up)
   ans1=0;
  else
   ans1=(rig-le)*(down-up); 
  ans2=(x[1]-x[0])*(y[1]-y[0])+(x[3]-x[2])*(y[3]-y[2]) - 2*ans1;
  ans3=10000-(ans2+ans1);
  cout<<"Night "<<t<<": "<<ans1<<" "<<ans2<<" "<<ans3<<"\n";  
 }
 //puts("ganteng");
 return 0;
}

