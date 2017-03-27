#include <cstdio>
#include <set>
#include <queue>
using namespace std;

set<int> s[7];
set<int>::reverse_iterator it;
int n,p,a,b;
long long ans;

int main(){
 scanf("%d %d",&n,&p);
 while(n--){
  scanf("%d %d",&a,&b);
  while(!s[a].empty()){
   it=s[a].rbegin();
   int now=*it;
   if(now>b)
    s[a].erase(now),ans++;
   else
    break;
  }
  if(s[a].empty()){
   ans++;
   s[a].insert(b);
  }
  else{
   it=s[a].rbegin();
   int now=*it;
   if(now!=b){
    s[a].insert(b);
    ans++;
   }
  }
 }
 printf("%lld\n",ans);
 return 0;
}