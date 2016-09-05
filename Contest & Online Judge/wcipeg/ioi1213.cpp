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

struct Node{
 int depth;
 char letter;
 int par[20];
 int next[26];
 
 Node(){
  depth = letter = 0;
  memset(next,-1,sizeof next);
  memset(par,-1,sizeof par);
 }
};

Node Trie[1000001];
int Trie_index[1000001];
int n,q;
char s[3];
int sz=1;

void Add_Trie(int now,int prev,char l){
 Trie[now].depth = Trie[prev].depth + 1;
 Trie[now].letter = l;
 Trie[now].par[0] = prev;
 for(int i = 1 ; (1<<i) <= Trie[now].depth ; i++){
  int tmp = Trie[now].par[i-1];
  int nxt = Trie[tmp].par[i-1];
  Trie[now].par[i] = nxt;
 }
}

int Add_Letter(int now,char l){
 if(Trie[now].next[l-'a'] != -1)
  return Trie[now].next[l-'a'];
 else{
  Trie[now].next[l-'a'] = sz;
  Add_Trie(sz,now,l);
  sz++;
  return sz-1;
 } 
}

char Query(int idx,int lvl){
 lvl = Trie[idx].depth - 1 - lvl;
 //if(lvl < 0){
  //return 'Q';
 //}
 int dep = Trie[idx].depth;
 for(int i = 0 ; (1<<i) <= lvl ; i++)
  if(lvl & (1<<i))
   idx = Trie[idx].par[i];
 return Trie[idx].letter;  
}

int main(){
 int it = 0;
 scanf("%d",&n);
 while(n--){
  scanf("%s",s);
  if(s[0] == 'T'){
   scanf("%s",s);
   it++;
   Trie_index[it] = Add_Letter(Trie_index[it-1],s[0]);
  }
  else if(s[0] == 'U'){
   scanf("%d",&q);
   it++;
   //if(q+1 > it){
    //puts("UNDO");
    //return 0;
  // }
   Trie_index[it] = Trie_index[it-q-1];
  }
  else{
   scanf("%d",&q);
   printf("%c\n",Query(Trie_index[it],q));
  }
 }
 //puts("ganteng");
 return 0;
}

