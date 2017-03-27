#include <cstdio>
using namespace std;

long long bit[1000005],b;
int n,q,a;
char x[10];

void update(int id,long long val){
 for(int i=id;i<=n;i+=i&-i)
  bit[i]+=val;
}

long long rsq(int id){
 long long res=0;
 for(int i=id;i;i-=i&-i)
  res+=bit[i];
 return res;
}

int main(){
 scanf("%d %d",&n,&q);
 while(q--){
  scanf("%s %d %lld",x,&a,&b);
  if(x[0]=='f')
   printf("%lld\n",rsq(b)-rsq(a-1));
  else
   update(a,b);
 }
 return 0;
}