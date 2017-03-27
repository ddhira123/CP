#include <cstdio>
#include <vector>
using namespace std;

struct trie{
int point[2];
int val;
};

long long ans;
vector<trie> v;
trie tmp;
int arr[20],n,k,tc,a,siz,sum;
#define g getchar_unlocked
inline int io(){
 char c;
 while(1){
  c=g();
  if(c!=' '&& c!='\n') break;
 }
 int ret=0,min=1;
 if(c=='-') min=-1;
 else ret=c-'0';
 while(1){
  c=g();
  if(c==' '|| c=='\n' || c==EOF) break;
  ret=(ret<<3)+(ret<<1)+c-'0';
 }
 return ret*min;
}


void add(int pos,int now){
 if(pos==-1)
  v[now].val++;
 else{
  if(v[now].point[arr[pos]]==-1){
   v[now].point[arr[pos]]=++siz;
   v.push_back(tmp);
  }
  add(pos-1,v[now].point[arr[pos]]);
  v[now].val=(v[now].point[1]!=-1 ? v[v[now].point[1]].val : 0)+(v[now].point[0]!=-1 ? v[v[now].point[0]].val : 0);
 }
}

void cek(int counter,int pos,int now){
 if(now==-1) return;
 else if(pos==-1 || counter+(1<<(pos+1))-1<k) ans+=(long long)v[now].val;
 else{
  cek(counter,pos-1,v[now].point[arr[pos]]);
  if((counter|(1<<pos))<k)
   cek(counter|(1<<pos),pos-1,v[now].point[1-arr[pos]]);
 }
}

int main(){
 tmp.point[0]=tmp.point[1]=-1;
 tmp.val=0;
 tc=io();
 while(tc--){
  ans=siz=sum=0;
  v.clear();
  v.push_back(tmp);
  for(int i=0;i<=17;i++)
   arr[i]=0;
  add(17,0);
  n=io();k=io();
  while(n--){
   a=io();
   sum^=a;
   for(int i=0;i<=17;i++)
    if(sum&(1<<i))
     arr[i]=1;
    else
     arr[i]=0;
   cek(0,17,0);
   add(17,0);
   //printf("%lld\n",ans);
  }
  printf("%lld\n",ans);
 }
 return 0;
}
