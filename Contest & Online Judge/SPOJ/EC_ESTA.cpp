#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define pq priority_queue
pq<unsigned,vector<unsigned>, greater<unsigned> > up;
pq<unsigned> down;
unsigned a,siz,siz2,tc,n;

int main(){
 scanf("%u",&tc);
 while(tc--){
 while(!up.empty()) up.pop();
 while(!down.empty()) down.pop();
 siz=siz2=0;
 scanf("%u",&n);
 for(unsigned i=0;i<n;i++){
   scanf("%u",&a);
   siz++;
   up.push(a);
   while(siz-siz2>=2){
    unsigned node=up.top();
    down.push(node);
    up.pop();
    siz--;
    siz2++;
   }
   if(siz>0 && siz2>0){
    while(1){
     unsigned node=up.top(),node2=down.top();
     if(node>=node2) break;
     else{
      up.pop(); down.pop();
      up.push(node2);
      down.push(node);
     }
    }
   }
   if((siz+siz2)&1){
    //prunsignedf("yee\n");
    unsigned node=up.top();
    printf("%u\n",node);
   }
   else{
    //prunsignedf("noo\n");
    unsigned node=down.top(),node2=up.top();
    printf("%u",(node+node2)/2);
    if((node+node2)&1)
     printf(".5");
    printf("\n");
   }
  }
 }
 return 0;
}