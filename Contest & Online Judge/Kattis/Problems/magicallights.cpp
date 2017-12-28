#include<bits/stdc++.h>
 
using namespace std;
 
#define ll long long
 
int curloc = 1;
ll bit[2][300005];
int loc[300005],ujung[300005];
vector <int> child[300005];
int n;
int color[300005];
 
void dfs(int pos){
 
loc[pos] = curloc++;
if(child[pos].size()==0){
ujung[pos] = loc[pos];
return;
}
 
int sz = child[pos].size();
for(int i = 0 ; i < sz ; i ++){
dfs(child[pos][i]);
}
 
ujung[pos] = ujung[child[pos][sz-1]];
//cout << pos << " " << loc[pos] << " " << ujung[pos] << endl;
}
 
void update(int p1, int p2){
int idx = 0;
if(p1>50) idx = 1, p1-=51;
for(;p2<=n;p2+=(p2&(-p2))) bit[idx][p2] ^= (1LL<<p1);
 
}
 
int query(int p1,int p2){
int ans = 0;
for(int idx=0;idx<2;idx++){
ll tmp1 = 0;
ll tmp2 = 0;
int pp2= p2;
int pp1 = p1;
for(;pp2>0;pp2-=(pp2&(-pp2))) tmp2^=bit[idx][pp2];
for(;pp1>0;pp1-=(pp1&(-pp1))) tmp1^=bit[idx][pp1];
ans+=__builtin_popcountll(tmp1 ^ tmp2);
}   
return ans;
}
 
int main(){
int q;
scanf("%d",&n);
scanf("%d",&q);
for(int i = 0 ; i < n; i++){
scanf("%d",&color[i]);
}
for(int i = 1; i < n; i++){
int tmp;
scanf("%d",&tmp);
child[tmp-1].push_back(i);
}
 
dfs(0);
 
for(int i = 0 ; i < n ; i ++){
update(color[i],loc[i]);
}
 
while(q--){
int cmd,tmp;
scanf("%d %d",&cmd ,&tmp);
tmp--;
 
if(cmd==0){
 
int ans = query(loc[tmp]-1,ujung[tmp]);
printf("%d\n",ans);
 
} else {
 
update(color[tmp],loc[tmp]);
update(cmd,loc[tmp]);
color[tmp]=cmd;
 
}
}
} 

