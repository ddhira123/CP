#include <cstdio>
using namespace std;

typedef long long LL;

const int M = 1000005;

LL arr[M];
LL n;
int m,tc;

bool Valid(){
 LL sum = 0;
 if(n == 0) return 0; // gak ada sweets
 for(int i = 0 ; i < m ; i++)
  sum += arr[i];
 if(sum == 0) return (n >= m);
 for(int i = 0 ; i < m ; i++)
  if(arr[i] == 0 || (n * arr[i]) % sum != 0) return 0;
 return 1;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%lld %d",&n,&m);
  for(int i = 0 ; i < m ; i++)
   scanf("%lld",&arr[i]);
  if(Valid()) puts("YES");
  else puts("NO");
 }
 return 0;
}
