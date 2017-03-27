#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

vector<int> op;
vector<bool> v;
int tc,len;
char x[105];

int main(){
 scanf("%d",&tc); getchar();
 while(tc--){
  op.clear(); v.clear();
  gets(x);
  len=strlen(x);
  for(int i=0;i<len;i++){
   if(x[i]=='A') op.push_back(2),i+=2;
   else if(x[i]=='O') op.push_back(1),i+=1;
   else if(x[i]=='N') op.push_back(0),i+=2;
   else if(x[i]=='T') v.push_back(1);
   else if(x[i]=='F') v.push_back(0);
   else if(x[i]==')'){
    int hm=op.back(); op.pop_back();
    if(hm==0){
     bool dum=v.back(); v.pop_back();
     v.push_back(!dum);
    }
    else{
     bool dum=v.back();v.pop_back();
     bool dum2=v.back();v.pop_back();
     if(hm==1) v.push_back(dum|dum2);
     else v.push_back(dum&dum2);
    }
   }
  }
  if(v.back()) puts("T");
  else puts("F");
 }
 return 0;
}
