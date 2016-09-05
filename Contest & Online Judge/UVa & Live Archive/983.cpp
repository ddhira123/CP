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

int n,m;
LL prefix[1005][1005],a,tot;
bool spasi;

int main(){
 while(scanf("%d %d",&n,&m)==2){
  if(spasi) puts("");
  else spasi=1;
  tot^=tot;
  for(int i=1;i<=n;i++)
   for(int j=1;j<=n;j++)
    scanf("%lld",&a),prefix[i][j]=prefix[i-1][j]+a;
  for(int i=m;i<=n;i++){
   LL sum=0;
   for(int j=1;j<m;j++)
    sum+=(prefix[i][j]-prefix[i-m][j]);
   for(int j=m;j<=n;j++){
    sum-=(prefix[i][j-m]-prefix[i-m][j-m]);
    sum+=(prefix[i][j]-prefix[i-m][j]);
    tot+=sum;
    printf("%lld\n",sum);
   } 
  }
  printf("%lld\n",tot);   
 }
 //puts("ganteng");
 return 0;
}
