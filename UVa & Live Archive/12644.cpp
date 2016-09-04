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

typedef pair<int,int> pii;
typedef long long LL;

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

int occur[505][30];
int counter[30];
int len;
char x[35];

vector<int> adj[505];
int match[1005];
int n,m;
bool vis[505];

int Augment(int v){
 if(vis[v]) return 0;
 vis[v]=1;
 for(int i=0;i<adj[v].size();i++){
  int u=adj[v][i];
  if(match[u]==-1 || Augment(match[u])){
   match[u]=v;
   return 1;
  }
 }
 return 0;
}

int main(){
 while(scanf("%d",&n)==1){
  scanf("%d",&m);
  for(int i=1;i<=n;i++){
   adj[i].clear();
   for(int j=0;j<26;j++) occur[i][j]=0;
   scanf("%s",x);
   len=strlen(x);
   for(int j=len-1;j>=0;j--)
    occur[i][x[j]-'a']++;
  }
  for(int i=1;i<=m;i++){
   match[n+i]=-1;
   for(int j=0;j<26;j++) counter[j]=0;
   scanf("%s",x);
   len=strlen(x);
   for(int j=len-1;j>=0;j--)
    counter[x[j]-'a']++;
   for(int j=1;j<=n;j++){
    bool valid=1;
    for(int k=0;k<26&&valid;k++)
     valid&=(occur[j][k]>=counter[k]);
    if(valid)
     adj[j].pb(i+n); 
   }
  }
  int ans=0;
  for(int i=1;i<=n&&ans<m;i++){
   for(int j=1;j<=n;j++) vis[j]=0;
   ans+=Augment(i);
  }
  printf("%d\n",ans);
 }
 //puts("ganteng");
 return 0;
}

