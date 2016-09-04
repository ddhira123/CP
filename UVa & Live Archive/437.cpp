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

vector<pair<pii,int> > v;
vector<int> LIS;
int arr[3],n,tc;

bool cmp(pair<pii,int> i,pair<pii,int> j){
 return i.fi.fi > j.fi.fi;
}

int main(){
 n=io();
 while(n){
  v.clear();
  LIS.clear();
  for(int i=0;i<n;i++){
   for(int j=0;j<3;j++)
    arr[j]=io();
   v.pb(mp(mp(max(arr[0],arr[1]),min(arr[0],arr[1])),arr[2])); 
   LIS.pb(0);
   v.pb(mp(mp(max(arr[0],arr[2]),min(arr[0],arr[2])),arr[1])); 
   LIS.pb(0);
   v.pb(mp(mp(max(arr[2],arr[1]),min(arr[2],arr[1])),arr[0])); 
   LIS.pb(0);   
  }
  sort(v.begin(),v.end(),cmp);
  int ans=0;
  for(int i=0;i<3*n;i++){
   for(int j=0;j<i;j++)
    if(v[j].fi.fi > v[i].fi.fi && v[j].fi.se > v[i].fi.se)
     LIS[i]=max(LIS[i],LIS[j]);
   LIS[i]+=v[i].se;
   ans=max(ans,LIS[i]);  
  }
  printf("Case %d: maximum height = %d\n",++tc,ans);
  n=io();
 }
 //puts("ganteng");
 return 0;
}

