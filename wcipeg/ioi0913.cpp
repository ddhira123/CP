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

pair<pii,int> arr[2005];
bool tmp[2005][2005];
int tot[2005];
int n,t,p;

bool cmp(pair<pii,int> i,pair<pii,int> j){
 if(i.fi.fi==j.fi.fi){
  if(i.fi.se==j.fi.se)
   return i.se<j.se;
  return i.fi.se>j.fi.se; 
 }
 return i.fi.fi>j.fi.fi;
}

int main(){
 SYNC;
 cin>>n>>t>>p;
 for(int i=1;i<=n;i++)
  arr[i].se=i;
 for(int i=1;i<=n;i++) 
  for(int j=1;j<=t;j++)
   cin>>tmp[i][j],tot[j]+=(!tmp[i][j]);
 for(int i=1;i<=n;i++)
  for(int j=1;j<=t;j++)
   if(tmp[i][j])
    arr[i].fi.se++,arr[i].fi.fi+=tot[j];
 sort(arr+1,arr+n+1,cmp);
 for(int i=1;i<=n;i++)
  if(arr[i].se==p)
   cout<<arr[i].fi.fi<<" "<<i<<"\n";     
 //puts("ganteng");
 return 0;
}

