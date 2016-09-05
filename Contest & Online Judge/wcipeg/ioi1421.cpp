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
#define MOD 1000000009LL
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
int seq[100005],tmp[100005];
int n;
vector<int> v;
pii proc[100005];

inline bool Query1(){
 for(int i=0;i<n;i++)
  tmp[i]=seq[i];
 sort(tmp,tmp+n);
 if(unique(tmp,tmp+n)-tmp < n) return 0;
 else{
  int st=-1;
  for(int i=0;i<n;i++)
   if(seq[i]<=n){
    st=i;
    break;
   }
  if(st==-1) return 1; 
  int cnt=seq[st];
  for(int i=st;i<n;i++){
   if(seq[i]<=n && cnt!=seq[i]) return 0;
   cnt++;
   if(cnt>n) cnt=1;
  }
  for(int i=0;i<st;i++){
   if(seq[i]<=n && cnt!=seq[i]) return 0;
   cnt++;
   if(cnt>n) cnt=1;
  }
  return 1;  
 } 
}

inline void Query2(){
 int st=-1;
 for(int i=0;i<n;i++)
  if(seq[i]<=n){
   st=i;
   break;
  }
 if(st==-1){
  for(int i=1;i<n;i++)
   proc[i]=mp(seq[i],i);
   proc[0]=mp(seq[0],n);
  } 
 else{
  int cnt=seq[st];
  for(int i=st;i<n;i++){
   proc[i]=mp(seq[i],cnt);
   cnt++;
   if(cnt>n) cnt=1;
  }
  for(int i=0;i<st;i++){
   proc[i]=mp(seq[i],cnt);
   cnt++;
   if(cnt>n) cnt=1;
  }
 }
 sort(proc,proc+n);
 int now=n+1;
 for(int i=0;i<n;i++){
  if(proc[i].fi!=proc[i].se){
   v.pb(proc[i].se);
   while(now<proc[i].fi)
    v.pb(now),now++;
   now=proc[i].fi+1;
  }
  //cout<<proc[i].fi<<" "<<proc[i].se<<"\n";   
 } 
}

LL modpow(LL base,LL po){
 LL ret=1;
 while(po){
  if(po&1) ret=(ret*base)%MOD;
  base*=base;
  base%=MOD;
  po>>=1;
 }
 return ret;
}

LL Query3(){
 if(!Query1()) return 0;
 int st=-1;
 for(int i=0;i<n;i++)
  if(seq[i]<=n){
   st=i;
   break;
  }
 if(st==-1){
  for(int i=1;i<n;i++)
   proc[i]=mp(seq[i],i);
   proc[0]=mp(seq[0],n);
  } 
 else{
  int cnt=seq[st];
  for(int i=st;i<n;i++){
   proc[i]=mp(seq[i],cnt);
   cnt++;
   if(cnt>n) cnt=1;
  }
  for(int i=0;i<st;i++){
   proc[i]=mp(seq[i],cnt);
   cnt++;
   if(cnt>n) cnt=1;
  }
 }
 sort(proc,proc+n);
 LL ans=1;
 int las=n+1;
 for(int i=0;i<n;i++)
  if(proc[i].fi!=proc[i].se){
   ans*=modpow(n-i,proc[i].fi-las);
   ans%=MOD;
   las=proc[i].fi+1;
  } 
 if(st==-1)
  ans=ans*(LL)(n);
 ans%=MOD;  
 return ans; 
}

int main(){
 SYNC;
 cin>>tc;
 cin>>n;
 for(int i=0;i<n;i++)
  cin>>seq[i];
 if(tc<=3)
  cout<<Query1()<<"\n";
 else if(tc<=6){
  Query2();
  cout<<(int)v.size();
  for(int i=0;i<v.size();i++)
   cout<<" "<<v[i];
  cout<<"\n"; 
 }  
 else
  cout<<Query3()<<"\n";
 //puts("ganteng");
 return 0;
}

