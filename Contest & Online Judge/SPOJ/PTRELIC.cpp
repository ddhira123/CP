#include <cstdio>
using namespace std;

long long l,r,h,m,s,ss,mid;
char z[50];

void cetak(long long x){
 ss=x%1000LL;
 x/=1000LL;
 s=x%60LL;
 x/=60LL;
 m=x%60LL;
 x/=60LL;
 h=x;
 printf("%lld:%02lld:%02lld:%03lld\n",h,m,s,ss);
}

bool tanya(long long x){
 cetak(x);
 fflush(stdout);
 scanf("%s",z);
 return z[0]=='P';
}

int main(){
 scanf("%lld:%lld:%lld:%lld",&h,&m,&s,&ss);
 l=0;
 r=h*60LL;
 r+=m;
 r*=60LL;
 r+=s;
 r*=1000LL;
 r+=ss;
 while(l<r){
  mid=(l+r+1)/2LL;
  if(tanya(mid))
    l=mid;
  else
    r=mid-1;
 }
 printf("PLATINUM: ");
 cetak(l);
 fflush(stdout);
 return 0;
}
