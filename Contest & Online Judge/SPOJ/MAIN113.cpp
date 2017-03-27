#include <cstdio>
using namespace std;

long long int isi[50],n,tc;

int main()
{isi[1]=3;
 isi[2]=9;
 for (n=3;n<=30;n++)
  isi[n]=2*isi[n-1]+isi[n-2];
 scanf("%lld",&tc);
 while(tc--){
  scanf("%lld",&n);
  printf("%lld\n",isi[n]);
 }
 return 0;
}
