#include <cstdio>
#include <algorithm>
using namespace std;
#define max_n 1000000
int sum[max_n+5],tc,a;
long long A[max_n+5];
int main(){
 for(int i=1;i<=max_n;i++)
  for(int j=i+i;j<=max_n;j+=i)
   sum[j]+=i;
 for(int i=2;i<=max_n;i++)
  A[i]=A[i-1]+sum[i];
 //printf("%lld\n",A[max_n]);
 //puts("ayaz");
 scanf("%d",&tc);
 while(tc--)
  scanf("%d",&a),printf("%lld\n",A[a]);
 return 0;
}
