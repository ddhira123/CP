#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> pii;
typedef long long LL;
#define fi first
#define se second
#define mp make_pair
priority_queue<pii> pq;
pii arr[300005];
int n,k,K[300005],it;
LL ans;

bool cmp(pii i,pii j){
 if(i.se==j.se)
  return i.fi>j.fi;
 return i.se<j.se;
}

int main(){
 scanf("%d %d",&n,&k);
 for(int i=0;i<n;i++)
  scanf("%d %d",&arr[i].se,&arr[i].fi);
 sort(arr,arr+n,cmp);
 for(int i=0;i<k;i++)
  scanf("%d",&K[i]);
 sort(K,K+k);
 for(int i=0;i<k;i++){
  while(it<n&&arr[it].se<=K[i])
   pq.push(arr[it++]);
  if(!pq.empty())
   ans+=(LL)pq.top().fi,pq.pop();
 }
 printf("%lld\n",ans);
 return 0;
}
