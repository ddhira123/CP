#include <iostream>
using namespace std;

struct node{
 char c;
 node *l,*r;
 node(char x){
  c=x;
  l=r=NULL;
 }
};

node *root;
string arr[105];

node *insert(node *x,int i,int haha){
 if(x==NULL){
  x=new node(arr[i][haha]);
  return x;
 }
 //cout<<x->c<<" "<<i<<" "<<pos<<"\n";
 if(arr[i][haha] < x->c)
  x->l=insert(x->l,i,haha);
 else
  x->r=insert(x->r,i,haha); 
 return x; 
}

void hapus(node *x){
 if(x==NULL) return;
 hapus(x->l);
 hapus(x->r);
 delete(x);
}

void pre(node *x){
 if(x==NULL) return;
 cout<<x->c;
 pre(x->l);
 pre(x->r);
}

int main(){
 root=NULL;
 while(1){
  int it=0;
  while(1){
   cin>>arr[it];
   if(arr[it][0]=='*' || arr[it][0]=='$') break;
   it++;
  }
  hapus(root);
  root=NULL;
  for(int i=it-1;i>=0;i--){
  // pos=0;
  //cout<<i<<"\n";
  for(int j=0;j<arr[i].length();j++)
   root=insert(root,i,j);
  }
  pre(root);
  cout<<"\n";
  if(arr[it][0]=='$') break;
 }
 return 0;
}
