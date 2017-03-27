#include <bits/stdc++.h>
using namespace std;

const int N = 10;

int arr[N][N];
int best[N][N];
int n;

int calc(vector<int> &v){
    sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    int pwr = 1;
    while(pwr <= v[0]) pwr <<= 1;
    pwr >>= 1;
    for(int i = 0 ; pwr >= 1 ; pwr >>= 1){
        int j = i;
        while(j < v.size() && (v[j] & pwr) == 0) j++;    
        if(j == v.size()) continue;
        swap(v[j],v[i]);
        for(int it = 0 ; it < v.size() ; it++)
            if(it != i && (v[it] & pwr) > 0)
                v[it] ^= v[i];
        i++;        
    }
    int res = 0;
    for(int i = 0 ; i < v.size() ; i++)
        res ^= v[i];
    return res;    
}

int calc_vertical(){
    for(int l = 1 ; l <= n ; l++){
        vector<int> v;
        for(int r = l ; r <= n ; r++){
            for(int row = 1 ; row <= n ; row++)
                v.push_back(arr[row][r]);
            best[l][r] = calc(v);    
        }
    }
    int res = 0;
    for(int i = 2 ; i <= n ; i++)
        for(int j = i ; j < n ; j++)
            res = max(res,best[1][i - 1] + best[i][j] + best[j + 1][n]);
    return res;        
}

int calc_horizontal(){
    for(int tp = 1 ; tp <= n ; tp++){
        vector<int> v;
        for(int bot = tp ; bot <= n ; bot++){
            for(int col = 1 ; col <= n ; col++)
                v.push_back(arr[bot][col]);
            best[tp][bot] = calc(v);    
        }
    }
    int res = 0;
    for(int i = 2 ; i <= n ; i++)
        for(int j = i ; j < n ; j++)
            res = max(res,best[1][i - 1] + best[i][j] + best[j + 1][n]);
    return res; 
}

void init(){
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; i++)
        for(int j = 1 ; j <= n ; j++)
            scanf("%d",&arr[i][j]);            
}

int main(){
    init();
    printf("%d\n",max(calc_vertical(),calc_horizontal()));
    return 0;
}