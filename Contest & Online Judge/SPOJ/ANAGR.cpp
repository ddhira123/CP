#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define fi first
#define se second
#define mp make_pair
typedef pair<int,int> pii;
int arr[2][30],n,tc;
char x[105],ans[105];
pii tmp[35];


int main(){
 scanf("%d",&tc); getchar();
 while(tc--){
  for(int a=0;a<2;a++){
   for(int b=0;b<26;b++)
    arr[a][b]=0;
   gets(x);
   n=strlen(x);
   for(int b=0;b<n;b++)
    if('a'<=x[b]&&x[b]<='z')
     arr[a][x[b]-'a']++;
    else if('A'<=x[b]&&x[b]<='Z')
     arr[a][x[b]-'A']++;
  }
  bool cek0=0,cek1=0;
  for(int a=0;a<26;a++)
   if(arr[0][a]>arr[1][a])
    cek1=1;
   else if(arr[0][a]<arr[1][a])
    cek0=1;
  if(!cek0&&!cek1)
   printf("YES\n");
  else if(cek0&&cek1)
   printf("NO LUCK\n");
  else if(cek1){
   int cnt=0,od=0,r=0,l=0,s=0;
   for(int a=0;a<26;a++){
    int dum=arr[0][a]-arr[1][a];
    od+=(dum&1);
    s+=dum;
    if(dum)
     tmp[cnt++]=mp(a,dum);
   }
   if(od>1)
    printf("NO LUCK\n");
   else{
    r=s-1;
    for(int a=0;a<cnt;a++){
     if(tmp[a].se&1){
      tmp[a].se--;
      ans[s/2]=tmp[a].fi;
     }
     while(tmp[a].se>0){
      ans[l++]=tmp[a].fi;
      ans[r--]=tmp[a].fi;
      tmp[a].se-=2;
     }
    }
    for(int a=0;a<s;a++)
     printf("%c",ans[a]+'a');
    printf("\n");
   }
  }
  else if(cek0){
   int cnt=0,od=0,r=0,l=0,s=0;
   for(int a=0;a<26;a++){
    int dum=arr[1][a]-arr[0][a];
    od+=(dum&1);
    s+=dum;
    if(dum)
     tmp[cnt++]=mp(a,dum);
   }
   if(od>1)
    printf("NO LUCK\n");
   else{
    r=s-1;
    for(int a=0;a<cnt;a++){
     if(tmp[a].se&1){
      tmp[a].se--;
      ans[s/2]=tmp[a].fi;
     }
     while(tmp[a].se>0){
      ans[l++]=tmp[a].fi;
      ans[r--]=tmp[a].fi;
      tmp[a].se-=2;
     }
    }
    for(int a=0;a<s;a++)
     printf("%c",ans[a]+'a');
    printf("\n");
   }
  }
 }
 return 0;
}
