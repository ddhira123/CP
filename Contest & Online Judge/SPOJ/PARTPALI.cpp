#include <cstdio>
using namespace std;

long long po[25],dp[1005][25],tc,n,k,a,b;



long long solve(long long sum,long long right){
 long long left=n-right-1;
 //printf("%lld %d %lld\n",sum,left,right);
 if(dp[sum][right]!=-1)
  return dp[sum][right];
 dp[sum][right]=0;
 if(left<right)
  return dp[sum][right]=(sum==0);
 if(left==right){
  for(long long i=0;i<10;i++)
   dp[sum][right]+=((((i*po[left])%k) + sum)%k==0);
  return dp[sum][right];
 }
 for(long long i=0;i<10;i++)
  dp[sum][right]+=solve( (sum+(((po[right]%k)*i)%k)+(((po[left]%k)*i)%k) )%k,right+1);
 return dp[sum][right];
}

int main(){
 po[0]=1;
 for(int i=1;i<20;i++)
  po[i]=po[i-1]*10;
 scanf("%lld",&tc);
 while(tc--){
  scanf("%lld %lld",&k,&n);
  for(a=0;a<=k;a++)
   for(b=0;b<=n;b++)
    dp[a][b]=-1;
   //memset(dp,-1,sizeof dp);
   if(n>1){
   long long res=0;
   for(long long i=1;i<10;i++)
    res+=solve( ( (((po[0]%k)*i)%k) + (((po[n-1]%k)*i)%k) )%k, 1);
   printf("%lld\n",res);
   }
   else
    printf("%lld\n",10/k-(10%k==0));
 }
 return 0;
}

