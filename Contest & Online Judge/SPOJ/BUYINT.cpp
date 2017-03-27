#include <cstdio>
using namespace std;

long long left,right,tc,n,i;

int main(){
 scanf("%lld",&tc);
 for(i=1;i<=tc;i++){
  scanf("%lld",&n);
  printf("Case %lld: ",i);
  left=1;right=40000;
  while(left<right){
   long long mid=(left+right)/2;
   if(mid*mid>n)
    right=mid;
   else
    left=mid+1;
  }
  left--;
  if(left*left==n)
   printf("0\n");
  else{
   right=left+1;
   long long k=(right*right)-(left*left)-1;
   n-=(left*left);
   if(n>(k/2))
    n=k-n+1;
   if(n%2==0)
    printf("%lld\n",n/2);
   else
    printf("%lld\n",n/2+(k/2-n+1));
  }
 }
 return 0;
}