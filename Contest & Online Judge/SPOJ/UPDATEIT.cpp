#include <cstdio>
using namespace std;

int bit[10005],tc,n,m,q,a,b,c;

void update(int idx,int val){
 for(int i=idx;i<=n;i+=i&-i)
  bit[i]+=val;
}

int query(int idx){
 int res=0;
 for(int i=idx;i;i-=i&-i)
  res+=bit[i];
 return res;
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  scanf("%d%d",&n,&m);
  for(a=1;a<=n;a++)
   bit[a]=0;
  while(m--){
   scanf("%d%d%d",&a,&b,&c);
   a++;b++;
   update(a,c);
   update(b+1,-c);
  }
  scanf("%d",&q);
  while(q--){
   scanf("%d",&a);
   a++;
   printf("%d\n",query(a));
  }
 }
 return 0;
}