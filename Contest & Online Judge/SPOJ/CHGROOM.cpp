#include <cstdio>
#include <vector>
using namespace std;

vector<long long> v;
bool prim[3200005];
long long n;

bool query(long long x){
 int ban=1,jum=0;
 for(int i=0;i<v.size()&&v[i]*v[i]<=x;i++)
  if(x%v[i]==0){
   jum++;
   int po=0;
   while(x%v[i]==0){
    x/=v[i];
    po++;
   }
   ban*=(po+1);
  }
 if(x>1){
  jum++;
  ban*=2;
 }
 if(ban==2)
  return 1;
 if(jum==1)
  return ban>=4;
 return ban>4;
}

int main(){
 for(int a=2;a<=3200000;a++)
  if(!prim[a]){
   v.push_back(a);
   for(int b=a;b<=3200000/a;b++)
    prim[a*b]=1;
  }
 scanf("%lld",&n);
 if(n==1)
  printf("ANNE\n");
 else if(query(n))
  printf("ANNE\n");
 else
  printf("MARIAN\n");
 return 0;
}
