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

typedef pair<int,int> pii;
typedef long long LL;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SYNC ios_base::sync_with_stdio(false)
#define g getchar_unlocked
#define INF 1000000000
#define INFLL 4000000000000000000LL
#define EPS 1e-9
#define MOD 1000000007LL

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

int tc;
int n;
pii arr[20005];
set<int> s;
vector<int> v;

bool cmp(pii a,pii b){
 if(a.fi==b.fi)
  return a.se<b.se;
 return a.fi>b.fi; 
}


int main(){
 tc=io();
 while(tc--){
  n=io();
  //s.clear();
  v.clear();
  for(int i=0;i<n;i++)
   arr[i].fi=io(),arr[i].se=io();
  sort(arr,arr+n,cmp);
  for(int i=0;i<n;i++){
   int idx=lower_bound(v.begin(),v.end(),arr[i].se+1)-v.begin();
   //printf("%d %d\n",idx,v.size);
   if(idx<v.size())
    v[idx]=arr[i].se;
   else 
    v.pb(arr[i].se); 
  } 
  printf("%d\n",(int)v.size());
 }
 //puts("ganteng");
 return 0;
}

