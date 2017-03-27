#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define INF 1000000000

vector<int> adj[100005],radj[100005];
int tc,n,a,b,dist[100005];
queue<int> q;

inline void reset(){
 for(int i=1;i<=n;i++)
  dist[i]=INF,adj[i].clear(),radj[i].clear();
}

inline void PlayBFS(){
 dist[n]=0;
 q.push(n);
 while(!q.empty()){
  int now=q.front(); q.pop();
  //printf("%d\n",now);
  for(int i=0;i<radj[now].size();i++)
   if(dist[radj[now][i]]==INF){
    dist[radj[now][i]]=dist[now]+1;
    q.push(radj[now][i]);
   }
 }
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  reset();
  for(int i=1;i<n;i++){
   scanf("%d",&a);
   while(a--)
    scanf("%d",&b),adj[i].push_back(b),radj[b].push_back(i);
  }
  for(int i=1;i<=n;i++)
   sort(adj[i].begin(),adj[i].end()),sort(radj[i].begin(),radj[i].end());
  PlayBFS();
  if(dist[1]==INF) puts("-1");
  else{
   vector<int> ans;
   ans.clear();
   ans.push_back(1);
   int now=1;
   while(now!=n)
    for(int i=0;i<adj[now].size();i++){
     int next=adj[now][i];
     if(dist[next]==dist[now]-1){
      ans.push_back(next);
      now=next;
      break;
     }
    }
   ans.pop_back();
   printf("%d\n",ans.size());
   for(int i=0;i<ans.size();i++){
    printf("%d",ans[i]);
    if(i<ans.size()-1) printf(" ");
    else printf("\n");
   }
  }
  puts("");
 }
 return 0;
}