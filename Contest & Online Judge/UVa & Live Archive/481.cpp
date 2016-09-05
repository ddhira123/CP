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

vector<int> BIT,LIS,uniq,v,ans;
int a,sz;

inline void make_unique(){
 sort(uniq.begin(),uniq.end());
 uniq.erase(unique(uniq.begin(),uniq.end()),uniq.end());
 sz=uniq.size();
 BIT.resize(sz+5);
}

inline void update(int pos,int v){
 for(int i=pos;i<=sz;i+=i&-i)
  BIT[i]=max(BIT[i],v);
}

inline int query(int pos){
 int ret=0;
 for(int i=pos;i;i-=i&-i)
  ret=max(ret,BIT[i]);
 return ret; 
}

int main(){
 while(scanf("%d",&a)==1)
  LIS.pb(0),v.pb(a),uniq.pb(a);
 make_unique();
 int maks=0,las=0;
 for(int i=0;i<v.size();i++){
  int pos=lower_bound(uniq.begin(),uniq.end(),v[i])-uniq.begin();
  LIS[i]=1+query(pos);
  if(LIS[i]>=maks)
   maks=LIS[i],las=i;
  update(pos+1,LIS[i]); 
 }
 printf("%d\n",maks);
 ans.pb(v[las]);
 maks--;
 for(int i=las-1;i>=0;i--)
  if(v[i]<v[las] && LIS[i]==maks)
   ans.pb(v[i]),las=i,maks--;
 printf("-\n");   
 for(int i=ans.size()-1;i>=0;i--)
  printf("%d\n",ans[i]);
 //puts("ganteng");
 return 0;
}

