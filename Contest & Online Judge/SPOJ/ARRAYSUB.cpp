#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

priority_queue<pair<int,int> > pq;
int n,k,arr[1000005],a;

int main(){
 scanf("%d",&n);
 for(a=0;a<n;a++)
  scanf("%d",&arr[a]);
 scanf("%d",&k);
 for(a=0;a<k;a++)
  pq.push(make_pair(arr[a],a));
 printf("%d",pq.top().first);
 for(a=k;a<n;a++){
  while(!pq.empty()&&pq.top().second<=a-k)
   pq.pop();
  pq.push(make_pair(arr[a],a));
  printf(" %d",pq.top().first);
 }
 printf("\n");
 return 0;
}
