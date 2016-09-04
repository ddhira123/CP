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

LL gcd(LL x,LL y){
 return y==0 ? x : gcd(y,x%y);
}

int n,q;
vector<LL> v;
LL arr[55];

int main(){
  SYNC;
  cin>>n>>q;
  while(n|q){
   v.clear();
   for(int i=0;i<n;i++)
    cin>>arr[i];
   for(int i=0;i<n;i++)
    for(int j=i+1;j<n;j++)
     for(int k=j+1;k<n;k++)
      for(int l=k+1;l<n;l++){
       LL ret=1;
       ret=(ret/gcd(ret,arr[i]))*arr[i];
       ret=(ret/gcd(ret,arr[j]))*arr[j];
       ret=(ret/gcd(ret,arr[k]))*arr[k];
       ret=(ret/gcd(ret,arr[l]))*arr[l];
       v.pb(ret);
      } 
   while(q--){
    LL a;
    cin>>a;
    LL ans1=-INFLL,ans2=INFLL;
    for(int i=0;i<v.size();i++){
     LL mul=a/v[i];
     ans1=max(ans1,mul*v[i]);
     if(mul*v[i]!=a) mul++;
     ans2=min(ans2,mul*v[i]);
    }
    cout<<ans1<<" "<<ans2<<"\n";
   }   
   cin>>n>>q;
  }
 //puts("ganteng");
 return 0;
}

