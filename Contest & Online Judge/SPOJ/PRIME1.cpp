#include <cstdio>
#include <vector>
using namespace std;

bool flag[31705];
vector<int> prime;
int tc,n,m;
bool isprime(int x){
 for(int idx=0;idx<prime.size()&&prime[idx]*prime[idx]<=x;idx++)
  if(x%prime[idx]==0)
   return 0;
  return x!=1;
}

int main(){
 for(int a=2;a<=31700;a++)
  if(!flag[a]){
   prime.push_back(a);
   for(int b=a;b<=31700/a;b++)
    flag[a*b]=1;
  }
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&m,&n);
  for(int a=m;a<=n;a++)
   if(isprime(a))
    printf("%d\n",a);
  if(tc)
   printf("\n");
 }
 return 0;
}
