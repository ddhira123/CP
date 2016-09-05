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

bool spasi;
int n,ans;
int arr[10005];
vector<int> v[10005];

int main(){
 n=io();
 while(n){
  for(int i=0;i<n;i++)
   arr[i]=io();
  sort(arr,arr+n);
  ans=0;
  int cnt=1;
  for(int i=1;i<n;i++)
   if(arr[i]==arr[i-1])
    cnt++;
   else
    ans=max(ans,cnt),cnt=1;
  ans=max(ans,cnt);
  
  priority_queue<pii> pq;
  vector<pii> tmp;
     
  for(int i=1;i<ans;i++)
   pq.push(mp(0,i)),v[i].clear();
  v[0].clear(); 
  v[0].pb(arr[0]);
  pq.push(mp(-1,0));
  for(int i=1;i<n;i++){
   if(arr[i]!=arr[i-1])
    while(!tmp.empty()) pq.push(tmp.back()),tmp.pop_back();
   pii haha=pq.top();
   pq.pop();
   v[haha.se].pb(arr[i]);
   haha.fi-=1;
   tmp.pb(haha); 
  }
  if(spasi) puts("");
  else      spasi=1;
  printf("%d\n",ans);
  for(int i=0;i<ans;i++){
   printf("%d",v[i][0]);
   for(int j=1;j<v[i].size();j++)
    printf(" %d",v[i][j]);
   puts(""); 
  }    
  n=io();
 }
 //puts("ganteng");
 return 0;
}

