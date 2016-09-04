#include <bits/stdc++.h>
using namespace std;

const int N = 15;

char s[N + 5][N + 5];
int n;

int rec(int row,int cmask,int dmask1,int dmask2){
    if(row == n)
        return 1;
    int res = 0;
    for(int col = 0 ; col < n ; col++)    
        if(s[row][col] != '*' && ( (cmask & (1 << col)) == 0)
         && ( (dmask1 & (1 << (row + col))) == 0)
         && ( (dmask2 & (1 << (col + n - 1 - row))) == 0) ){
            res += rec(row + 1,cmask | (1 << col),dmask1 | (1 << (row + col)),dmask2 | (1 << (col + n - 1 - row)));
         }
    return res;     
}

int main(){
    int tc = 0;
    scanf("%d",&n);
    while(n){
        for(int i = 0 ; i < n ; i++)
            scanf("%s",s[i]);
        printf("Case %d: %d\n",++tc,rec(0,0,0,0));    
        scanf("%d",&n);
    }
    return 0;
}
