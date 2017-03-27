#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct prefix{
 int next;
 int counter;
} trie[100005][30][2];

char c[105];
int n,s,cnt,ans;

void add(int now,int pos,int id){
 if(pos==s)
  return;
 if(trie[now][c[pos]-'A'][id].next==-1)
   trie[now][c[pos]-'A'][id].next=cnt++;
 trie[now][c[pos]-'A'][id].counter++;
 add(trie[now][c[pos]-'A'][id].next,pos+1,id);
}

int rec(int now0,int now1,int depth){
 int res=0;
 for(int i=0;i<26;i++)
  if(trie[now0][i][0].next==-1||trie[now1][i][1].next==-1){}
  else{
   ans+=(min(trie[now0][i][0].counter,trie[now1][i][1].counter)-rec(trie[now0][i][0].next,trie[now1][i][1].next,depth+1))*(depth+1);
   res+=min(trie[now0][i][0].counter,trie[now1][i][1].counter);
  }
 return res;
}

int main(){
 scanf("%d",&n);
 while(n!=-1){
  for(int i=0;i<=100000;i++)
   for(int j=0;j<26;j++)
    for(int k=0;k<2;k++){
     trie[i][j][k].next=-1;
     trie[i][j][k].counter=0;
    //printf("%d %d\n",i,j);
   }
  cnt=1;
  for(int i=0;i<n;i++){
   scanf("%s",c);
   s=strlen(c);
   add(0,0,0);
  }
  cnt=1;
  for(int i=0;i<n;i++){
   scanf("%s",c);
   s=strlen(c);
   add(0,0,1);
  }
  ans=0;
  int tmp=rec(0,0,0);
  printf("%d\n",ans);
  scanf("%d",&n);
 }
 return 0;
}
