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

int tc;
int n,m;
int a,b;
queue<int> q;
int par[100005];
int val[100005];
vector<int> v[10005];
int tot[100005];

int finds(int x){
 int y=x,z;
 while(y!=par[y]) y=par[y];
 while(x!=y){
  z=par[x];
  par[x]=y;
  x=z;
 }
 return y;
}

int main(){
 tc=io();
 while(tc--){
  n=io(),m=io();
  for(int i=1;i<=n;i++)
   par[i]=i,tot[i]=1;
  int k=n-1;
  while(m--){
   a=io(),b=io();
   a=finds(a),b=finds(b);
   if(a!=b)
    k--,tot[b]+=tot[a],tot[a]=0,par[a]=b;
  }
  for(int i=1;i<=n;i++){
   a=io();
   val[i]=a;
   v[a].pb(i);
  }
  while(!q.empty()) q.pop();
  int sum=0;
  //cout<<k<<"\n";
  for(int i=1;i<=10000;i++)
   while(!v[i].empty()){
    int lol=v[i].back();
    v[i].pop_back();
    if(!q.empty()){
    int lol2=q.front();
    if(finds(lol) != finds(lol2) && tot[finds(lol)] + tot[finds(lol2)] - 2 != 0){
     k--;
     //cout<<lol<<" "<<lol2<<"\n";
     sum+= i + val[lol2];
     tot[finds(lol2)]+=tot[finds(lol)]-2;
     tot[finds(lol)]=0;
     par[finds(lol)] = finds(lol2);
     q.pop();
    }
    else
     q.push(lol);
    }
    else
     q.push(lol);
   }
   //cout<<k<<" "<<sum<<"\n";
   if(k==1 && q.size()==2){
    while(!q.empty()){
     int lol=q.front();
     q.pop();
     sum+=val[lol];
    }
   }
   else if(k)
    sum=-1;
   printf("%d\n",sum);
 }
 //puts("ganteng");
 return 0;
}

