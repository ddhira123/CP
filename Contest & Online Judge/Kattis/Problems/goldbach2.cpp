#include <bits/stdc++.h>
using namespace std;

const int N = 32000;

bool flag[N + 5];

void sieve(){
    flag[1] = 1;
    for(int i = 2 ; i <= N ; i++)
        if(!flag[i]){
            for(int j = i + i ; j <= N ; j += i)
                flag[j] = 1;
    }           
}

int main(){
    sieve();
    int tc,n;
    scanf("%d",&tc);
    for(int t = 1 ; t <= tc ; t++){
        if(t > 1) puts("");
        scanf("%d",&n);
        vector<int> ans;
        for(int i = 2 ; i <= (n) / 2 ; i++)
            if(!flag[i] && !flag[n - i])
                ans.push_back(i);
        printf("%d has %d representation(s)\n",n,(int)ans.size());
        for(int i = 0 ; i < ans.size() ; i++)
            printf("%d+%d\n",ans[i],n-ans[i]);      
    }
    return 0;
}

