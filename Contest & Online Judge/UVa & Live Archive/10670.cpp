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

int tc;
int m,n,q;
pair<string,int> arr[105];

bool cmp(pair<string,int> a,pair<string,int> b){
 if(a.se==b.se) return a.fi<b.fi;
 return a.se<b.se;
}

inline int solve(int a,int b){
 int l=m;
 int ret=0;
 while(2*n < l){
  int nxt=(l)>>1;
  ret+=min(b,(l-nxt)*a);
  l=nxt;
 }
 if((l)/2 == n) 
  ret+=min(b,(l-n)*a);
 else ret+=(l-n)*a;
 return ret;
}

inline int stnum(string tmp){
 int ret=0;
 for(int i=0;i<tmp.length();i++)
  ret=(ret<<3)+(ret<<1)+tmp[i]-'0';
 return ret; 
}

int main(){
 SYNC;
 cin>>tc;
 for(int t=1;t<=tc;t++){
  cin>>m>>n>>q;
  for(int i=0;i<q;i++){
   int a,b;
   string s;
   cin>>s;
   string tmp="";
   for(int j=0;j<s.length();j++)
    if(s[j]==':')
     arr[i].fi=tmp,tmp="";
    else if(s[j]==',')
     a=stnum(tmp),tmp="";
    else
     tmp=tmp+s[j]; 
   b=stnum(tmp);   
   arr[i].se=solve(a,b);
  }
  sort(arr,arr+q,cmp);
  cout<<"Case "<<t<<"\n";
  for(int i=0;i<q;i++)
   cout<<arr[i].fi<<" "<<arr[i].se<<"\n";
 }
 //puts("ganteng");
 return 0;
}

