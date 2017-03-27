#include <cstdio>
#include <queue>
#include <stack>
using namespace std;
stack<int> s;
queue<int> q;
int n,a,cnt;

int main(){
 scanf("%d",&n);
 while(n){
  while(!q.empty())
   q.pop();
  while(!s.empty())
   s.pop();
  while(n--){
   scanf("%d",&a);
   q.push(a);
  }
  cnt=1;
  while(!q.empty()){
   a=q.front();
   q.pop();
   while(!s.empty()&&s.top()==cnt){
    cnt++;
    s.pop();
   }
   s.push(a);
  }
  while(!s.empty()&&s.top()==cnt){
   cnt++;
   s.pop();
  }
  if(s.empty())
   printf("yes\n");
  else
   printf("no\n");
  scanf("%d",&n);
 }
 return 0;
}
