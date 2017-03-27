#include <cstdio>
#include <algorithm>
#define eps 1e-9
using namespace std;
typedef pair<double,double> pdd;
#define fi first
#define se second
#define mp make_pair

int siz,tc,op,n,q;
double x1,x2,y1,y2,pos;
pdd arr[2005];

int main(){
 scanf("%d",&tc);
 while(tc--){
  siz=0;
  scanf("%d",&n);
  while(n--)
   scanf("%lf %lf %lf %lf",&x1,&y1,&x2,&y2),arr[siz++]=mp(min(x1,x2),max(x1,x2));
  scanf("%d",&q);
  while(q--){
   scanf("%d",&op);
   if(op)
    scanf("%lf %lf %lf %lf",&x1,&y1,&x2,&y2),arr[siz++]=mp(min(x1,x2),max(x1,x2));
   else{
    scanf("%lf",&pos);
    int cnt=0;
    for(int i=0;i<siz;i++)
     if(arr[i].fi<pos+eps && pos<arr[i].se+eps)
      cnt++;
    printf("%d\n",cnt);
   }
  }
 }
 return 0;
}
