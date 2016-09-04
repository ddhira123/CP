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

char s[25],x[25];
LL k,fact;
int tc;
vector<int> v,ans;

int main(){
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
  scanf("%s %lld",s,&k);
  fact=1;
  int len=strlen(s);
  ans.clear();
  for(LL i=1;i<=len;i++)
   v.pb(i-1),fact*=i;
  printf("Case %d: ",t);
  for(LL i=len;i>=1;i--){
   fact/=i;
   LL pos=(k-1)/fact;
   k-=fact*pos;
   //printf("%c",s[v[pos]]);
   ans.pb(v[pos]);
   v.erase(v.begin()+pos);
  } 
  for(int i=0;i<len;i++)
   x[ans[i]]=s[i];
  for(int i=0;i<len;i++)
   printf("%c",x[i]); 
  puts("");
 }
 //puts("ganteng");
 return 0;
}

