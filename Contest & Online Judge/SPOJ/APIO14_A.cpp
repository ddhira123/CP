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
#define MAX_N 300000
struct node{
 int next[26];
 int sufflink;
 int len;
 int occ;
};

node Tree[MAX_N + 5];
int deg[MAX_N + 5];
char s[MAX_N + 5];
int sz,last;

inline void Solve(){
 queue<int> q;
 for(int i=1;i<=sz;i++)
  if(deg[i]==0) q.push(i);
 LL ans=0; 
 while(!q.empty()){
  int id=q.front();
  q.pop();
  ans=max(ans,(LL)Tree[id].len*(LL)Tree[id].occ);
  int nxt=Tree[id].sufflink;
  Tree[nxt].occ+=Tree[id].occ;
  deg[nxt]--;
  if(deg[nxt]==0) q.push(nxt);
 } 
 printf("%lld\n",ans);
}

inline void Add(int pos){
 int cur=last,curlen;
 int letter=s[pos]-'a';
 while(1){
  curlen=Tree[cur].len;
  if(pos - 1 - curlen >= 0 && s[pos-1-curlen] == s[pos])
   break;
  cur=Tree[cur].sufflink; 
 }
 if(Tree[cur].next[letter]){
  last=Tree[cur].next[letter];
  Tree[last].occ++;
  return;
 }
 sz++;
 last=sz;
 Tree[sz].len=Tree[cur].len+2;
 Tree[cur].next[letter]=sz;
 if(Tree[sz].len==1){
  Tree[sz].occ=1;
  Tree[sz].sufflink=2;
  deg[2]++;
  return;
 }
 while(1){
  cur=Tree[cur].sufflink;
  curlen=Tree[cur].len;
  if(pos-1-curlen >= 0 && s[pos-1-curlen] == s[pos]){
    Tree[sz].sufflink=Tree[cur].next[letter];
    deg[Tree[sz].sufflink]++;
    break;
  }
 }
 Tree[sz].occ=1;
}

int main(){
 sz=2,last=2;
 Tree[1].sufflink=Tree[2].sufflink=1;
 deg[1]=2;
 Tree[1].len=-1;
 scanf("%s",s);
 int len=strlen(s);
 for(int i=0;i<len;i++)
  Add(i);
 Solve(); 
 //puts("ganteng");
 return 0;
}
