#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

char x[100005];
int n,d,a,tc;
vector<char> v;
int main(){
 //scanf("%d %d",&n,&d);
 //while(n|d){
 scanf("%d",&tc);
 while(tc--){
  scanf("%s %d",x,&d);
  v.clear();
  n=strlen(x);
  for(a=0;a<n;a++){
   while(!v.empty()&&d>0&&x[a]>v.back()){
    v.pop_back();
    d--;
   }
   v.push_back(x[a]);
  }
  while(d--)
   v.pop_back();
  if(v.empty())
   v.push_back('0');
  for(a=0;a<v.size();a++)
   printf("%c",v[a]);
  printf("\n");
  //scanf("%d %d",&n,&d);
 }
 return 0;
}
