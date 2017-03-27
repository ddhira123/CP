#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

vector<int> pos[MAXN];
vector<int> ch[MAXN];
char s[MAXN];
int pset[MAXN];
int tc,q,len;

int finds(int x){
    return x == pset[x] ? x : pset[x] = finds(pset[x]);
}

void join(int x,int y){
    x = finds(x);
    y = finds(y);
    pset[x] = y;
}

void reset(){
    len = strlen(s);
    for(int i = 0 ; i < len ; i++){
        pset[i] = i;        
        ch[i].clear();
        pos[i].clear();
    }    
}

void read(){
    scanf("%s",s);
    reset();
    scanf("%d",&q);
    while(q--){
        int a,b;
        scanf("%d %d",&a,&b);
        join(a,b);
    }
}

void process(){
    for(int i = 0 ; i < len ; i++){
        int x = finds(i);
        ch[x].push_back(s[i]);
        pos[x].push_back(i);
    }
    for(int i = 0 ; i < len ; i++){
        sort(ch[i].begin(),ch[i].end());
        sort(pos[i].begin(),pos[i].end());
        for(int j = 0 ; j < pos[i].size() ; j++)
            s[ pos[i][j] ] = ch[i][j];
    }
    puts(s);
}

int main(){
    scanf("%d",&tc);
    for(int T = 1 ; T <= tc ; T++){
        read();
        process();
    }
    return 0;
}

