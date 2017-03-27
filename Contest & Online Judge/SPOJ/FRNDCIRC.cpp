#include <cstdio>
#include <string>
#include <map>
using namespace std;

int par[200005],siz[200005],n,tc,cnt;
string y,z;
char x[2][25];
map<string,int> m;

inline void gen(int l){
 for(int i=0;i<l;i++)
  siz[i]=1,par[i]=i;
}

int finds(int i){
 if(i==par[i]) return i;
 return par[i]=finds(par[i]);
}

int main(){
 scanf("%d",&tc);
 while(tc--){
  cnt=0; m.clear();
  scanf("%d",&n);
  gen(2*n);
  while(n--){
   scanf("%s %s",x[0],x[1]);
   y=(string) x[0];
   z=(string) x[1];
   if(m.find(y)==m.end()) m[y]=cnt++;
   if(m.find(z)==m.end()) m[z]=cnt++;
   int i=m[y],j=m[z];
   if(finds(i)==finds(j))
    printf("%d\n",siz[finds(i)]);
   else{
    siz[finds(i)]+=siz[finds(j)];
    siz[finds(j)]=0;
    par[finds(j)]=finds(i);
    printf("%d\n",siz[finds(i)]);
   }
  }
 }
 return 0;
}
