#include <cstdio>
#include <vector>
using namespace std;

vector<int> op;
long long n,i,j;

long long gcd(long long x,long long y){
 if(y==0)
  return x;
 return gcd(y,x%y);
}

int main(){
 scanf("%lld",&n);
 while(n){
  op.clear();
  i=j=1;
  while(n>1){
   if(n%2==1){
    op.push_back(1);
    n=(n-1)/2;
   }
   else{
    op.push_back(0);
    n/=2;
   }
  }
  for(int a=op.size()-1;a>=0;a--)
   if(op[a])
    i+=j;
   else
    j+=i;
  long long div=gcd(i,j);
  printf("%lld/%lld\n",i/div,j/div);
  scanf("%lld",&n);
 }
 return 0;
}