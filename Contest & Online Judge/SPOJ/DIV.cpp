#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int fak[1000005],a,b;
bool flag[1000005],prim[1000005];
vector<int> v;

int main(){
 for(a=1;a<=1000000;a++)
  for(b=1;b<=1000000/a;b++)
   fak[a*b]++;
 for(a=2;a<=1000000;a++)
  if(!flag[a]){
   v.push_back(a);
   for(b=a;b<=1000000/a;b++)
    flag[a*b]=1;
  }
 for(a=0;a<v.size();a++)
  for(b=a+1;b<v.size()&&v[b]<=1000000/v[a];b++)
   prim[v[a]*v[b]]=1;
 int cnt=0;
 for(a=1;a<=1000000;a++)
  if(prim[fak[a]]){
   cnt++;
   if(cnt==9){
    cnt=0;
    printf("%d\n",a);
    //getchar();
   }
  }
 return 0;
}