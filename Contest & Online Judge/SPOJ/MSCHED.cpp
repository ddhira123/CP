#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pq priority_queue
int n;
pii arr[10005];
pq<pii> q;

bool cmp(pii i,pii j){
 return i.se>j.se;
}

int main(){
 scanf("%d",&n);
 for(int i=0;i<n;i++)
  scanf("%d %d",&arr[i].fi,&arr[i].se);
 sort(arr,arr+n,cmp);
 int i=0,ans=0;
 for(int j=10000;j>0;j--){
  while(i<n && j<=arr[i].se)
   q.push(arr[i++]);
  if(!q.empty()){
   pii tmp=q.top();
   q.pop();
   ans+=tmp.fi;
  }
 }
 printf("%d\n",ans);
 return 0;
}
