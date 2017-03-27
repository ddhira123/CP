#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define max_n 120000
int h,p,s,a,b,ans,maks,num[max_n+5],low[max_n+5],counter[max_n+5],tc,cnt,visited[max_n+5];
vector<int> S,adj[max_n+5];

#define g getchar_unlocked
inline int io(){
register char c;
while(1){
c=g();
if((c^32) && (c^10)) break;
}
register int res=c-'0';
while(1){
c=g();
if(!(c^32) || !(c^10))
return res;
res=(res<<3)+(res<<1)+(c-'0');
}
}


void PlayTarjan(int v){
 num[v]=low[v]=cnt++;
 S.push_back(v);
 visited[v]=1;
 for(int i=0;i<adj[v].size();i++){
  int u=adj[v][i];
  if(visited[u]==-1)
   PlayTarjan(u);
  if(visited[u]==1)
   low[v]=min(low[v],low[u]);
 }
 if(low[v]==num[v])
  while(1){
   int u=S.back(); S.pop_back();
   visited[u]=0; low[u]=low[v];
   if(u>1000) counter[low[v]]++;
   if(u==v) break;
  }
}

int main(){
 for(int i=0;i<=max_n;i++)
  visited[i]=num[i]=low[i]=-1;
 tc=io();
 while(tc--){
  ans=0; maks=-1;
  for(int i=0;i<=cnt;i++)
   counter[i]=0;
  for(int i=1;i<=h;i++){
   visited[i]=low[i]=num[i]=-1;
   adj[i].clear();
  }
  for(int i=1001;i<=1000+p;i++){
   visited[i]=low[i]=num[i]=-1;
   adj[i].clear();
  }
  cnt=0;
  h=io(); p=io(); s=io();
  while(s--){
   a=io(); b=io();
   adj[a].push_back(b);
  }
  for(int i=1;i<=h;i++)
   if(visited[i]==-1)
    PlayTarjan(i);
  for(int i=1001;i<=1000+p;i++)
   if(visited[i]==-1)
    PlayTarjan(i);
  for(int i=1;i<=h;i++)
   if(maks<counter[low[i]]){
    ans=i;
    maks=counter[low[i]];
   }
  printf("%d %d\n",ans,maks);
 }
 return 0;
}
