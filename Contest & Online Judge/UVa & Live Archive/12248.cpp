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

vector<pii> wish;
vector<int> uniq;
int cnt[200005],par[200005];
int n,m;

void Make(){
 sort(wish.begin(),wish.end());
 sort(uniq.begin(),uniq.end());
 wish.erase(unique(wish.begin(),wish.end()),wish.end());
 uniq.erase(unique(uniq.begin(),uniq.end()),uniq.end());
 for(int i=0;i<uniq.size();i++)
  cnt[i]=0,par[i]=i;
 //for(int i=0;i<wish.size();i++)
  //printf("%d %d\n",wish[i].fi,wish[i].se); 
 //for(int i=0;i<uniq.size();i++)
  //printf("%d\n",uniq[i]); 
}

int ID(int x){
 return lower_bound(uniq.begin(),uniq.end(),x)-uniq.begin();
}

bool cekcount(){
 for(int i=0;i<wish.size();i++){
  int a=wish[i].fi,b=wish[i].se;
  a=ID(a),b=ID(b);
  cnt[a]++,cnt[b]++;
  if(cnt[a] == 3 || cnt[b] == 3) return 0;
 }
 return 1;
}

int finds(int x){
 return x==par[x] ? x : par[x]=finds(par[x]);
}

bool cekcycle(){
 for(int i=0;i<wish.size();i++){
  int a=wish[i].fi,b=wish[i].se;
  a=ID(a),b=ID(b);
  if(finds(a)!=finds(b))
   par[finds(a)]=finds(b);
  else{
   if(i==wish.size()-1 && wish.size() == n) return 1;
   else return 0;
  }   
 }
 return 1;
}


int main(){
 scanf("%d %d",&n,&m);
 while(n|m){
  uniq.clear();
  wish.clear();
  for(int i=0;i<m;i++){
   int a,b;
   scanf("%d %d",&a,&b);
   wish.pb(mp(min(a,b),max(a,b)));
   uniq.pb(a),uniq.pb(b);
  }
  Make();
  bool haha=0;
  if(cekcount()){
   //puts("C");
   if(cekcycle()){
    //puts("D");
    //if(cekfinal()){
     //puts("E");
     haha=1;
    //} 
   }
  }
  printf("%c\n",haha ? 'Y' : 'N');
  scanf("%d %d",&n,&m);
 }
 //puts("ganteng");
 return 0;
}

