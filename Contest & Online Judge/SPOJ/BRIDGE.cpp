#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
typedef pair<int,int> ii;
#define fi first
#define se second
#define mp make_pair
#define N 1005
ii arr[N];
int tmp[N],siz,ans,tc,bit[N],n;
map<int,int> m;

bool cmp(ii i,ii j){
 if(i.fi==j.fi)
  return i.se<j.se;
 return i.fi<j.fi;
}

inline void update(int pos,int val){
 for(int i=pos;i<=siz;i+=i&-i)
  bit[i]=max(bit[i],val);
}

inline int query(int pos){
 int ret=0;
 for(int i=pos;i;i-=i&-i)
  ret=max(ret,bit[i]);
 return ret;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  siz=1,ans=0;
  m.clear();
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
   scanf("%d",&tmp[i]),arr[i].se=tmp[i];
  for(int i=1;i<=n;i++)
   scanf("%d",&arr[i].fi);
  sort(tmp+1,tmp+n+1);
  sort(arr+1,arr+n+1,cmp);
  for(int i=1;i<=n;i++)
   if(m.find(tmp[i])==m.end()){
    m[tmp[i]]=siz;
    bit[siz++]=0;
   }
  for(int i=1;i<=n;i++){
   int res=1+query(m[arr[i].se]);
   //printf("%d %d %d -> %d\n",arr[i].fi,arr[i].se,m[arr[i].se],res);
   ans=max(ans,res);
   update(m[arr[i].se],res);
  }
  printf("%d\n",ans);
 }
 return 0;
}