#include <cstdio>
#include <cstring>
using namespace std;

char x[20];
int val[1000005],pos[1000005],op[1000005],n,fi[1000005];
long long m;

int res(int st,int fin){
 long long hm=fin-st;
 m-=fin;
 m%=hm;
 return fi[st+m];
}

void proc(){
 long long cnt=0,post=1;
 while(post<=n){
  //printf("%lld %lld\n",post,cnt);
  if(op[post]==-1){
   cnt++;
   if(val[post]!=-1){
    printf("%d\n",res(val[post],cnt));
    return;
   }
   if(cnt==m){
    printf("%d\n",post);
    return;
   }
   fi[cnt]=post;
   val[post]=cnt;
   post++;
  }
  else if(op[post]==0){
   if(val[post]==cnt){
    printf("TLE\n");
    return;
   }
   val[post]=cnt;
   post++;
  }
  else{
   if(val[post]==cnt){
    printf("TLE\n");
    return;
   }
   val[post]=cnt;
   post=pos[op[post]];
  }
 }
 printf("WA\n");
}

int main(){
 scanf("%d %lld",&n,&m); getchar();
 for(int i=1;i<=n;i++){
  gets(x);
  val[i]=-1;
  fi[i]=-1;
  if(x[0]=='c')
   op[i]=-1;
  else if(x[0]=='g'){
   int s=strlen(x),dum=0;
   for(int j=5;j<s-1;j++){
    dum*=10;
    dum+=x[j]-'0';
   }
   op[i]=dum;
  }
 else{
   int s=strlen(x),dum=0;
   for(int j=0;j<s-1;j++){
    dum*=10;
    dum+=x[j]-'0';
   }
   op[i]=0;
   pos[dum]=i;
  }
  //printf("%d\n",op[i]);
 }
 proc();
 return 0;
}
