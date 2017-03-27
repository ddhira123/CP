#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100001;
const int M = 7;

struct Node{
    int next[10];
    int res;
    
    Node(){
        memset(next,-1,sizeof next);
        res = 0;
    }
};

Node trie[N * M];
char s[M + 5];
int n,len,sz;

int Get(int pos,int s_pos,bool udah,int add){
    if(s_pos == len) return trie[pos].res + add;
    int ret = 0;
    if(!udah){
        for(int i = 0 ; i < 10 ; i++)
            if(trie[pos].next[i] != -1)
                ret = max(ret,Get(trie[pos].next[i],s_pos + 1,i != s[s_pos] - '0',abs(i - (int)(s[s_pos] - '0'))));
    }
    else if(trie[pos].next[s[s_pos] - '0'] != -1)
        ret = Get(trie[pos].next[s[s_pos] - '0'],s_pos + 1,udah,add);
    return ret;    
}

void Update(int pos,int s_pos,int val){
    if(s_pos == len) trie[pos].res = val;
    else{
        if(trie[pos].next[s[s_pos] - '0'] == -1)
            trie[pos].next[s[s_pos] - '0'] = ++sz;
        Update(trie[pos].next[s[s_pos] - '0'],s_pos + 1,val);    
    }
}

int main(){
    scanf("%d",&n);
    int ans = 0;
    for(int i = 0 ; i < n ; i++){
        scanf("%s",s);
        len = strlen(s);
        int tmp = Get(0,0,0,0);
        ans = max(ans,tmp);
        Update(0,0,tmp);
    }
    printf("%d\n",ans);
    return 0;
} 