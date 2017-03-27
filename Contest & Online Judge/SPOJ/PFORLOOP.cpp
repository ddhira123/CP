#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
pii x,tmp;
int z;
set<pii> s;
set<pii>::iterator it;

int main(){
 while(scanf("%d",&z)==1){
  x=mp(z,z);
  it=s.lower_bound(x);
  if(it!=s.end()){
   tmp=*it;
   if(tmp.fi==x.se+1){
    s.erase(tmp);
    x.se=tmp.se;
   }
  }
  it=s.lower_bound(x);
  if(it!=s.begin()){
   it--;
   tmp=*it;
   if(tmp.se+1==x.fi){
    x.fi=tmp.fi;
    s.erase(tmp);
   }
  }
  s.insert(x);
 }
 while(!s.empty()){
  x=*s.begin();
  s.erase(s.begin());
  printf("for (int i = %d; i <= %d; i++) cout << i << %c %c;",x.fi,x.se,34,34);
  printf("\n");
 }
 return 0;
}