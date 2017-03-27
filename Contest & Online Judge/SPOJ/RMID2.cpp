#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define pq priority_queue
pq<int,vector<int>, greater<int> > up;
pq<int> down;
int a,siz,siz2,tc;

#define g getchar_unlocked
inline int io(){
 char c;
 while(1){
 c=g();
 if(c!=' ' && c!='\n')
  break;
 }
 int res=0; bool min=0;
 if(c=='-')min=1;
 else res=c-'0';
 while(1){
 c=g();
 if(c==' ' || c=='\n' || c==EOF)
  break;
 res=(res<<1)+(res<<3)+(c-'0');
 }
 if(min)res*=-1; return res;
}


int main(){
 tc=io();
 while(tc--){
 while(!up.empty()) up.pop();
 while(!down.empty()) down.pop();
 siz=siz2=0;
 a=io();
 while(a){
   while(siz-siz2>=2){
    int node=up.top();
    down.push(node);
    up.pop();
    siz--;
    siz2++;
   }
   if(siz>0 && siz2>0){
    while(1){
     int node=up.top(),node2=down.top();
     if(node>=node2) break;
     else{
      up.pop(); down.pop();
      up.push(node2);
      down.push(node);
     }
    }
   }
  if(a>0){
   siz++;
   up.push(a);
  }
  else if(a==-1){
   if((siz+siz2)&1){
    //printf("yee\n");
    siz--;
    int node=up.top();
    up.pop();
    printf("%d\n",node);
   }
   else{
    //printf("noo\n");
    siz2--;
    int node=down.top();
    down.pop();
    printf("%d\n",node);
   }
  }
  a=io();
  }
 }
 return 0;
}
