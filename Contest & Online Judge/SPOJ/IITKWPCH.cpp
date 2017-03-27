#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

long long C[3][1000005],ans;
bool bit[1030],dum[15];
int freq[1030],freq2[1030],tc,n,s;
vector<int> tmp[1030];
char c[25];

bool cou(int x){
 int res=0;
 while(x){
  res++;
  x&=(x-1);
 }
 return res&1;
}

int main(){
 for(int i=1;i<1024;i++){
  bit[i]=cou(i);
  for(int j=i,k=0;j>0;j>>=1,k++)
   if(j&1)
    tmp[i].push_back(k);
 }
 for(int i=0;i<=1000000;i++)
  C[0][i]=1;
 for(int i=1;i<3;i++)
  for(int j=i;j<=1000000;j++)
   C[i][j]=C[i][j-1]+C[i-1][j-1];
 scanf("%d",&tc);
 while(tc--){
  scanf("%d",&n);
  for(int i=0;i<1024;i++)
   freq[i]=freq2[i]=0;
  while(n--){
   scanf("%s",c);
   s=strlen(c);
   for(int i=0;i<10;i++)
    dum[i]=0;
   for(int i=0;i<s;i++)
    dum[c[i]-'0']=1;
   int sum=0;
   for(int i=0;i<10;i++)
    if(dum[i])
     sum|=(1<<i);
   freq2[sum]++;
  }
  for(int i=1;i<1024;i++)
   for(int j=1;j<(1<<tmp[i].size());j++){
    int sum=0;
    for(int k=0;k<tmp[i].size();k++)
     if(j&(1<<k))
      sum|=(1<<tmp[i][k]);
    freq[sum]+=freq2[i];
   }
  ans=0;
  for(int i=1;i<1024;i++)
   if(bit[i])
    ans+=C[2][freq[i]];
   else
    ans-=C[2][freq[i]];
  printf("%lld\n",ans);
 }
 return 0;
}