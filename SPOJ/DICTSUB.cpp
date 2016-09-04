#include <bits/stdc++.h>
using namespace std;

const int LETTER = 26;
const int N = 10005;

vector<int> pos[LETTER];
char s[N];
int n,tc,len;

void init(){
    for(int i = 0 ; i < LETTER ; i++)
        pos[i].clear();
    scanf("%d %s",&n,s);
    len = strlen(s);
    //printf("%d %s\n",n,s);
    for(int i = 0 ; i < len ; i++)
        pos[s[i] - 'A'].push_back(i);    
}

void solve(){
    for(int i = 0 ; i < n ; i++){
        scanf("%s",s);
        len = strlen(s);
        int last = -1;
        bool ok = 1;
        for(int j = 0 ; j < len ;){
            int k = j;
            int num = 0;
            while('0' <= s[k] && s[k] <= '9'){
                num = (num * 10 + (int)(s[k] - '0'));
                k++;
            }
            int letter = s[k] - 'A';
            int lol = upper_bound(pos[letter].begin(),pos[letter].end(),last) - pos[letter].begin();
            //printf("letter %d lol %d num %d size %d\n",letter,lol,num,(int)pos[letter].size());
            if((int)pos[letter].size() - lol < num){
                ok = 0;
            }
            else{
                last = pos[letter][lol + num - 1];
            }
            j = k + 1;
        }
        printf("%s\n",ok ? "YES" : "NO");
    }
    puts("");
}

int main(){
    scanf("%d",&tc);
    for(int t = 1 ; t <= tc ; t++){
        init();
        solve();
    }
    return 0;
}
