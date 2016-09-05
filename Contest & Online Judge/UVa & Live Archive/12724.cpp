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

struct node{
 int next[26];
 string st;
 inline void reset(){
  st="";
  for(int i=0;i<26;i++)
   next[i]=-1;
 }
};

node trie[5005];
int sz,len;
string s,tmp,dum;
int tc,n,m;
int occ[300];

inline void insert(){
 int pos=0;
 for(int i=0;i<len;i++){
  if(trie[pos].next[tmp[i]-'a']==-1)
   trie[sz].reset(),trie[pos].next[tmp[i]-'a']=sz++;
  pos=trie[pos].next[tmp[i]-'a']; 
 }
 trie[pos].st=s;
}

inline string search(){
 int pos=0;
 for(int i=0;i<len;i++)
  pos=trie[pos].next[tmp[i]-'a'];
 return trie[pos].st; 
}

inline void countsort(){
 for(int i=0;i<len;i++)
  occ[s[i]]++;
 tmp="";
 for(char i='a';i<='z';i++)
  while(occ[i]>0)
   occ[i]--,tmp=tmp+i;   
}

int main(){
 //TIE;
 //SYNC;
 cin>>tc;
 //cout<<tc<<"\n";
 for(int t=1;t<=tc;t++){
  trie[0].reset();
  sz=1;
  cin>>n>>m;
  //cout<<n<<" "<<m<<"\n";
  for(int i=0;i<n;i++){
   cin>>s;
   //cout<<s<<"\n";
   len=s.length();
   countsort();
   //cout<<tmp<<"\n";
   insert();
   //DEBUG;
  }
  getline(cin,s);
  cout<<"Case #"<<t<<":\n";
  while(m--){
   getline(cin,dum);
   int len2=dum.length();
   bool spasi=0;
   s="";
   for(int i=0;i<len2;i++)
    if(dum[i]==' '){
     if(s!=""){
     //cout<<s<<"\n";
     len=s.length();
     countsort();
     if(spasi) cout<<" ";
     else      spasi=1;
     cout<<search();
     s="";
     }
    }
   else
    s=s+dum[i];
   if(s!=""){
    len=s.length();
    countsort();
    if(spasi) cout<<" ";
    else      spasi=1;
    cout<<search();
    s="";
   }
   cout<<"\n";
  }
 }
 //puts("ganteng");
 return 0;
}

