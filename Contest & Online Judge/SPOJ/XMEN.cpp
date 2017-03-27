#include <cstdio>
#include <set>
using namespace std;

set<int> s;
set<int>::iterator it;
int tc,n,arr[100005],pos[100005],b,a;

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(a=1;a<=n;a++)
   scanf("%d",&arr[a]);
  for(a=1;a<=n;a++){
   scanf("%d",&b);
   pos[b]=a;
  }
  s.clear();
  for(a=1;a<=n;a++){
   s.insert(pos[arr[a]]);
   it=s.find(pos[arr[a]]);
   it++;
   if(it!=s.end())
    s.erase(it);
  }
  int siz=s.size();
  printf("%d\n",siz);
 }
 return 0;
}
