#include <bits/stdc++.h>
using namespace std;

int operate(int a,int b,int tipe){
    if(tipe == 0) return a + b;
    if(tipe == 1) return a - b;
    if(tipe == 2) return a * b;
    return a / b;   
}


int simulate(int a,int b,int c){
    vector<int> v;
    vector<int> op;
    op.push_back(a);
    op.push_back(b);
    op.push_back(c);
    for(int i = 0 ; i < 4 ; i++)
        v.push_back(4);
    for(int i = 0 ; i < 3 ; i++){
        int high = 0;
        for(int j = 1 ; j < op.size() ; j++)
            if(op[j] / 2 > op[high] / 2)
                high = j;
        v[high] = operate(v[high],v[high + 1],op[high]);
        op.erase(op.begin() + high);
        v.erase(v.begin() + high + 1);      
    }   
    return v[0];
}

char conv(int x){
    if(x == 0) return '+';
    if(x == 1) return '-';
    if(x == 2) return '*';
    return '/';
}

int main(){
    int tc;
    scanf("%d",&tc);
    while(tc--){
        int n;
        scanf("%d",&n);
        bool ada = 0;
        for(int i = 0 ; i < 4 ; i++)
            for(int j = 0 ; j < 4 ; j++)
                for(int k = 0 ; k < 4 ; k++){
                    if(simulate(i,j,k) == n){
                        printf("4 %c 4 %c 4 %c 4 = %d\n",conv(i),conv(j),conv(k),n);
                        ada = 1;
                        goto hell;
                    }
                }
        hell:       
        if(!ada)
            puts("no solution");
    }
    return 0;
}

