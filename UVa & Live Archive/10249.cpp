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

bool cmp(pii a,pii b){
 if(a.fi==b.fi)
  return a.se<b.se;
 return a.fi>b.fi; 
}

pii team[75];
priority_queue<pii> pq;
vector<int> ans[75];
vector<pii> dum;
int n,m,d;

inline void Solve(){
 dum.clear();
 for(int i=0;i<n;i++){
  while(team[i].fi--){
   if(pq.empty()){
    puts("0");
    return;
   }
   pii tmp=pq.top(); pq.pop();
   ans[team[i].se].pb(tmp.se);
   tmp.fi--;
   if(tmp.fi) dum.pb(tmp);
  }
  while(!dum.empty())
   pq.push(dum.back()),dum.pop_back();
 }
 puts("1");
 for(int i=0;i<n;i++){
  printf("%d",ans[i][0]);
  for(int j=1;j<ans[i].size();j++)
   printf(" %d",ans[i][j]);
  puts(""); 
 }
}

int main(){
 n=io(),m=io();
 while(n|m){
  while(!pq.empty()) pq.pop();
  for(int i=0;i<n;i++)
   scanf("%d",&team[i].fi),team[i].se=i,ans[i].clear();
  for(int i=0;i<m;i++)
   scanf("%d",&d),pq.push(mp(d,i+1));
  Solve();  
  n=io(),m=io();
 }
 //puts("ganteng");
 return 0;
}

