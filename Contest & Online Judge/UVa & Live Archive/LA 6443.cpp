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

const int MAXX = 1000000;

void add(int &x,int y){
 x+=y;
 if(x >= MOD) x-=MOD;
 if(x < 0)    x+=MOD;
}

int BIT[5][MAXX+5];

void Update(int id,int x,int val){
 x++;
 for(; x <= MAXX ; x+= x&-x)
  add(BIT[id][x],val);
}

LL val(int id,LL x){
 LL ans,ans2,ans3;
 if(id == 0)
  ans = x + 1;
 else if(id == 1){
  ans = x;
  ans2 = x+1;
  
  if(ans%2 == 0) ans/=2;
  else ans2/=2;
  
  ans=(ans*ans2)%MOD;
 } 
 else if(id == 2){
  ans = x;
  ans2 = x+1;
  ans3 = x*2LL + 1;
  
  if(ans%2 == 0) ans/=2;
  else if(ans2%2 == 0) ans2/=2;
  else ans3/=2;
  
  if(ans%3 == 0) ans/=3;
  else if(ans2%3 == 0) ans2/=3;
  else ans3/=3;  
  
  ans = (ans * ans2) % MOD;
  ans = (ans * ans3) % MOD;
 }
 else{
  ans2 = val(1,x);
  ans = (ans2 * ans2)%MOD;
 }
 //printf("%d %lld %lld\n",id,x,ans);
 return ans;
}

LL Query(int idx){
 //printf("NOW %d\n",idx);
 int subs=0,tot[4] = {0,0,0,0};
 for(int i = idx+1 ; i ; i-= i&-i){
  //printf("%d\n",i);
  for(int j=0;j<4;j++){
   add(tot[j],BIT[j][i]);
  }
  add(subs,BIT[4][i]);
 }
 //DEBUG;
 LL ret = -subs;
 for(int i = 0 ; i < 4 ; i++)
  ret = (ret + (LL)tot[i] * val(i,idx)) % MOD;
 if (ret < 0) ret += MOD; 
 return ret; 
}

int tc,q;

void Update2(LL st,LL en,LL a,LL b,LL c,LL d){
 //puts("UP");
 int tmp=0,tmp2=0; // tmp : dari a, tmp2 : dari b+1
 LL lol;
 
 Update(0,st,d);
 Update(0,en+1,-d);
 
 Update(1,st,c);
 Update(1,en+1,-c);
 
 Update(2,st,b);
 Update(2,en+1,-b);
 
 Update(3,st,a);
 Update(3,en+1,-a);
 
 //if(st){
 lol = (val(0,st-1) * d)%MOD;
 add(tmp,lol);
 lol = (val(1,st-1) * c)%MOD;
 add(tmp,lol); 
 lol = (val(2,st-1) * b)%MOD;
 add(tmp,lol);
 lol = (val(3,st-1) * a)%MOD;
 add(tmp,lol);
 Update(4,st,tmp);
 //}
 
 lol = (val(0,en) * d)%MOD;
 add(tmp2,lol);
 lol = (val(1,en) * c)%MOD;
 add(tmp2,lol); 
 lol = (val(2,en) * b)%MOD;
 add(tmp2,lol);
 lol = (val(3,en) * a)%MOD;
 add(tmp2,lol);
 Update(4,en+1,-tmp2); 
}

LL Query2(LL st,LL en,LL a,LL b,LL c,LL d){
 LL ans = Query(en) - Query(st-1);
 while(ans >= MOD) ans -= MOD;
 while(ans < 0) ans += MOD;
 LL lol=MAXX;
 LL tmp=(ans*st)%lol;
 LL tmp2=(ans*en)%lol;
 if(tmp > tmp2) swap(tmp,tmp2);
 Update2(tmp,tmp2,a,b,c,d);
 return ans;
}

int main(){
 scanf("%d",&tc);
 for(int T=1;T<=tc;T++){
  printf("Case #%d:\n",T);
  memset(BIT,0,sizeof BIT);
  scanf("%d",&q);
  while(q--){
   char s[5];
   LL a,b,c,d,st,en;
   scanf("%s %lld %lld %lld %lld %lld %lld",s,&st,&en,&a,&b,&c,&d);
   //scanf("%s",s);
   //st = io() ; en = io() ; a = io() ; b = io() ; c = io() ; d = io();
   while(a >= MOD) a-= MOD; while(a < 0) a+= MOD;
   while(b >= MOD) b-= MOD; while(b < 0) b+= MOD;   
   while(c >= MOD) c-= MOD; while(c < 0) c+= MOD;
   while(d >= MOD) d-= MOD; while(d < 0) d+= MOD;      
   //assert(st >=0 && st<MAXX && en >=0 && en<MAXX);
   if(s[0] == 'p')
    Update2(st,en,a,b,c,d);
   else
    printf("%lld\n",Query2(st,en,a,b,c,d));
  }
 }
 //assert(0);
 //puts("ganteng");
 return 0;
}

