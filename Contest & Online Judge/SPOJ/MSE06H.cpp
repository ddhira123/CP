#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second

vector<pii> v;
pii tmp;
long long ans,bit[1005];
int tc,n,m,k;

void update(int pos){
 for(int i=pos;i<=m;i+=i&-i)
  bit[i]+=1LL;
}

long long query(int pos){
 long long res=0;
 for(int i=pos;i;i-=i&-i)
  res+=bit[i];
 return res;
}

bool cmp(pii i,pii j){
 if(i.fi==j.fi)
  return i.se<j.se;
 return i.fi<j.fi;
}

int main(){
 scanf("%d",&tc);
 for(int t=1;t<=tc;t++){
  scanf("%d %d %d",&n,&m,&k);
  v.clear();
  for(int i=0;i<k;i++){
   scanf("%d %d",&tmp.fi,&tmp.se);
   v.push_back(tmp);
  }
  for(int i=1;i<=m;i++)
   bit[i]=0;
  ans=0;
  sort(v.begin(),v.end(),cmp);
  for(int i=0;i<k;i++){
   ans+=query(m)-query(v[i].se);
   update(v[i].se);
  }
  printf("Test case %d: %lld\n",t,ans);
 }
 return 0;
}