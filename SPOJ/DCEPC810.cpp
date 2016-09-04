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

int dp[30][30][2][2];
char a[30],txt[30],b[30];
int lena,lenb,lentxt;

int solve(int pos,int posab,bool mor,bool les){
 //printf("%d %d %d %d\n",pos,posab,mor,les);
 if(pos == lentxt) return (posab > 0 && (mor || posab >= lena) && (les || posab <= lenb));
 int &ret = dp[pos][posab][mor][les];
 if(ret != -1) return ret;
 ret = solve(pos+1,posab,mor,les);
 if((posab >= lena || (lena > posab && (mor || txt[pos] >= a[posab])))
    && ((les) || (lenb > posab && (les || txt[pos] <= b[posab]))))
    ret += solve(pos+1,posab+1,mor||(posab >= lena)||(posab < lena && txt[pos] > a[posab]),les||(posab < lenb && txt[pos] < b[posab]));
 return ret;
}

int main(){
 memset(dp,-1,sizeof dp);
 scanf("%s %s %s",txt,a,b);
 lentxt = strlen(txt), lena = strlen(a), lenb = strlen(b);
 printf("%d\n",solve(0,0,0,0));
 return 0;
}
