#include <cstdio>
#include <set>
using namespace std;

int bit[300005],n,a;
set<int> s;
set<int>::iterator it;
long long ans;
void update(int idx,int val){
 for(int i=idx;i<=n;i+=i&-i)
  bit[i]+=val;
}

int query(int idx){
 int res=0;
 for(int i=idx;i;i-=i&-i)
  res+=bit[i];
 return res;
}

int main(){
 scanf("%d",&n);
 s.insert(0);
 s.insert(n);
 for(int i=1;i<=n;i++){
  scanf("%d",&a);
  ans+=query(a);
  printf("%lld\n",ans);
  it=s.lower_bound(a);
  int hi=*it;it--;
  int lo=*it;
  update(lo+1,1);
  update(hi+1,-1);
  s.insert(a);
  //for(int j=1;j<=n;j++)
   //printf("%d -> %d\n",j,query(j));
 }
 return 0;
}
