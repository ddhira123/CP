#include <cstdio>
#include <vector>
using namespace std;

vector<int> prime;
bool flag[1005];
int tc,a,b;

int gcd(int i,int j){
 if(j==0)
  return i;
 return gcd(j,i%j);
}

int numdiv(int n){
 int res=1;
 for(int i=0;i<prime.size()&&prime[i]*prime[i]<=n;i++){
  int p=0;
  while(n%prime[i]==0){
   p++;
   n/=prime[i];
  }
  res*=(p+1);
 }
 if(n!=1) res*=2;
 return res;
}

int main(){
 for(a=2;a<=1000;a++)
  if(!flag[a]){
   prime.push_back(a);
   for(b=a;b<=1000/a;b++)
    flag[a*b]=1;
  }
 scanf("%d",&tc);
 while(tc--){
  scanf("%d %d",&a,&b);
  printf("%d\n",numdiv(gcd(a,b)));
 }
 return 0;
}