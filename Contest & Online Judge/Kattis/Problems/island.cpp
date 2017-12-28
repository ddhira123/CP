#include <bits/stdc++.h>
using namespace std;

const int N = 85;

int dr[4] = {-1,0,1,0};
int dc[4] = {0,-1,0,1};

string petak[N];
int num[N][N];
int pset[N * N];
int sz;
int bridge,island;
int r,c;
vector<int> seen;

void dfsnum(int rr,int cc){
    num[rr][cc] = sz;
    for(int i = 0 ; i < 4 ; i++){
        int nr = rr + dr[i];
        int nc = cc + dc[i];
        if(nr >= 0 && nr < r && nc >= 0 && nc < c && num[nr][nc] == -1 && (petak[nr][nc] == '#' || petak[nr][nc] == 'X')){
            dfsnum(nr,nc);
        }
    }   
}

void dfscon(int rr,int cc){
    num[rr][cc] = 1;
    for(int i = 0 ; i < 4 ; i++){
        int nr = rr + dr[i];
        int nc = cc + dc[i];
        if(nr >= 0 && nr < r && nc >= 0 && nc < c){
            if(petak[nr][nc] == 'X')
                seen.push_back(num[nr][nc]);
            else if(petak[nr][nc] == 'B' && num[nr][nc] == -1)
                dfscon(nr,nc);  
        }
    }
}

void init(){
    for(int i = 0 ; i < N * N ; i++)
        pset[i] = i;
}

int finds(int x){
    return pset[x] == x ? x : pset[x] = finds(pset[x]);
}

void join(int x,int y){
    pset[finds(x)] = finds(y);
}

int main(){
    int tc = 0;
    while(getline(cin,petak[0])){
        r = 1;
        c = petak[0].length();
        //cout << petak[0] << endl;
        while(getline(cin,petak[r])){
            if(petak[r][0] != '.' && petak[r][0] != '#' && petak[r][0] != 'B' && petak[r][0] != 'X') break;
            //printf("%c\n",petak[r][0]);
            //cout << petak[r] << endl;
            r++; 
        }
        sz = 0;
        memset(num,-1,sizeof num);
        init();
        for(int i = 0 ; i < r ; i++)
            for(int j = 0 ; j < c ; j++)
                if(num[i][j] == -1 && (petak[i][j] == 'X' || petak[i][j] == '#')){
                    sz++;
                    dfsnum(i,j);
                }   
        bridge = 0;     
        for(int i = 0 ; i < r ; i++)
            for(int j = 0 ; j < c ; j++)
                if(num[i][j] == -1 && petak[i][j]== 'B'){
                    seen.clear();
                    dfscon(i,j);
                    for(int k = 1 ; k < seen.size() ; k++)
                        join(seen[0],seen[k]);
                    bridge++;   
                }                   
        island = sz;
        int need = 0;
        for(int i = 1 ; i <= sz ; i++)
            if(finds(i) == i) need++;
        if(tc) puts("");
        tc++;       
        printf("Map %d\n",tc);
        printf("islands: %d\n",island);
        printf("bridges: %d\n",bridge);
        printf("buses needed: %d\n",need);          
    }
    return 0;
} 

