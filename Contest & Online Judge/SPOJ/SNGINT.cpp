#include <cstdio>
#include <vector>
using namespace std;

vector<int> v;
int a,n,tc;

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  if(n==0)
   printf("10\n");
  else if(n==1)
   printf("1\n");
  else{
   for(a=9;a>=2;a--)
    while(n%a==0){
     n/=a;
     v.push_back(a);
    }
   if(n!=1){
    v.clear();
    printf("-1\n");
   }
   else{
    while(!v.empty()){
     printf("%d",v.back());
     v.pop_back();
    }
    printf("\n");
   }
  }
 }
 return 0;
}